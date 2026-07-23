#include "MaterialGraphDSLBridge.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "Dom/JsonObject.h"
#include "MaterialEditingLibrary.h"
#include "MaterialShared.h"
#include "Materials/Material.h"
#include "Materials/MaterialExpressionCustom.h"
#include "Materials/MaterialExpressionFunctionInput.h"
#include "Materials/MaterialExpressionFunctionOutput.h"
#include "Materials/MaterialFunction.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "ShaderCompiler.h"
#include "ToolsetRegistry/ToolsetLibrary.h"

namespace
{
	TArray<UMaterialExpression*> GetExpressions(UObject* MaterialOrFunction)
	{
		if (UMaterial* Material = Cast<UMaterial>(MaterialOrFunction))
		{
			return Material->GetExpressionCollection().Expressions;
		}
		if (UMaterialFunction* Function = Cast<UMaterialFunction>(MaterialOrFunction))
		{
			return Function->GetExpressionCollection().Expressions;
		}
		return {};
	}

	TArray<FAssetData> GetReferencingMaterials(UMaterialFunction* MaterialFunction)
	{
		TArray<FAssetData> Result;
		if (!MaterialFunction)
		{
			return Result;
		}

		FAssetRegistryModule& Module =
			FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
		TArray<FName> Referencers;
		Module.Get().GetReferencers(
			MaterialFunction->GetOutermost()->GetFName(),
			Referencers,
			UE::AssetRegistry::EDependencyCategory::All);
		for (const FName Referencer : Referencers)
		{
			TArray<FAssetData> Assets;
			Module.Get().GetAssetsByPackageName(Referencer, Assets);
			for (const FAssetData& AssetData : Assets)
			{
				if (AssetData.AssetClassPath.GetAssetName() == UMaterial::StaticClass()->GetFName())
				{
					Result.Add(AssetData);
				}
			}
		}
		return Result;
	}

	FString GetOutputName(const UMaterialExpression* Expression, const int32 OutputIndex)
	{
		if (!Expression)
		{
			return {};
		}
		const TArray<FExpressionOutput>& Outputs =
			const_cast<UMaterialExpression*>(Expression)->GetOutputs();
		if (!Outputs.IsValidIndex(OutputIndex) || Outputs[OutputIndex].OutputName.IsNone())
		{
			return {};
		}
		return Outputs[OutputIndex].OutputName.ToString();
	}

	FString ToPythonEnumName(const FString& NativeName)
	{
		FString Result;
		Result.Reserve(NativeName.Len() + 8);
		for (int32 Index = 0; Index < NativeName.Len(); ++Index)
		{
			const TCHAR Character = NativeName[Index];
			if (Index > 0 && FChar::IsUpper(Character) &&
				FChar::IsLower(NativeName[Index - 1]))
			{
				Result.AppendChar(TEXT('_'));
			}
			Result.AppendChar(FChar::ToUpper(Character));
		}
		return Result;
	}

	TSharedPtr<FJsonObject> ReadEditableProperties(const UMaterialExpression* Expression)
	{
		TArray<FName> PropertyNames;
		for (TFieldIterator<FProperty> It(
				 Expression->GetClass(),
				 EFieldIterationFlags::IncludeSuper);
			 It;
			 ++It)
		{
			const FProperty* Property = *It;
			const bool bCustomPinProperty = Expression->IsA<UMaterialExpressionCustom>() &&
				(Property->GetFName() ==
					 GET_MEMBER_NAME_CHECKED(UMaterialExpressionCustom, Inputs) ||
				 Property->GetFName() ==
					 GET_MEMBER_NAME_CHECKED(UMaterialExpressionCustom, AdditionalOutputs));
			if (Property->HasAnyPropertyFlags(CPF_Edit) &&
				!Property->HasAnyPropertyFlags(CPF_EditConst | CPF_Transient | CPF_Deprecated) &&
				!bCustomPinProperty &&
				Property->GetFName() !=
					GET_MEMBER_NAME_CHECKED(
						UMaterialExpression,
						MaterialExpressionEditorX) &&
				Property->GetFName() !=
					GET_MEMBER_NAME_CHECKED(
						UMaterialExpression,
						MaterialExpressionEditorY))
			{
				PropertyNames.Add(Property->GetFName());
			}
		}

		TSharedPtr<FJsonObject> Result = MakeShared<FJsonObject>();
		const FString Json = UToolsetLibrary::GetObjectProperties(Expression, PropertyNames);
		const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Json);
		FJsonSerializer::Deserialize(Reader, Result);
		return Result;
	}

	FString GuidToDsl(const FGuid& Guid)
	{
		return Guid.IsValid()
			? Guid.ToString(EGuidFormats::DigitsWithHyphensLower)
			: FString();
	}

	FString Slugify(const FString& Value)
	{
		FString Result;
		bool bLastWasUnderscore = false;
		for (const TCHAR Character : Value)
		{
			if (FChar::IsAlnum(Character))
			{
				if (!Result.IsEmpty() &&
					FChar::IsUpper(Character) &&
					FChar::IsLower(Result[Result.Len() - 1]))
				{
					Result.AppendChar(TEXT('_'));
				}
				Result.AppendChar(FChar::ToLower(Character));
				bLastWasUnderscore = false;
			}
			else if (!Result.IsEmpty() && !bLastWasUnderscore)
			{
				Result.AppendChar(TEXT('_'));
				bLastWasUnderscore = true;
			}
		}
		while (Result.EndsWith(TEXT("_")))
		{
			Result.LeftChopInline(1);
		}
		return Result.IsEmpty() ? TEXT("node") : Result;
	}

	FString ReadNameProperty(const UObject* Object, const FName PropertyName)
	{
		if (const FNameProperty* Property =
				FindFProperty<FNameProperty>(Object->GetClass(), PropertyName))
		{
			return Property->GetPropertyValue_InContainer(Object).ToString();
		}
		return {};
	}

	FString MakeSemanticNodeId(
		const UMaterialExpression* Expression,
		TSet<FString>& UsedIds)
	{
		FString Candidate;
		if (Expression->IsA<UMaterialExpressionFunctionInput>())
		{
			Candidate = TEXT("input_") + ReadNameProperty(Expression, TEXT("InputName"));
		}
		else if (Expression->IsA<UMaterialExpressionFunctionOutput>())
		{
			Candidate = TEXT("output_") + ReadNameProperty(Expression, TEXT("OutputName"));
		}
		else
		{
			Candidate = ReadNameProperty(Expression, TEXT("ParameterName"));
			if (Candidate.IsEmpty())
			{
				Candidate = Expression->Desc;
			}
			if (Candidate.IsEmpty())
			{
				Candidate = Expression->GetClass()->GetName();
				Candidate.RemoveFromStart(TEXT("MaterialExpression"));
			}
		}

		const FString Base = Slugify(Candidate);
		Candidate = Base;
		for (int32 Suffix = 2; UsedIds.Contains(Candidate); ++Suffix)
		{
			Candidate = FString::Printf(TEXT("%s_%02d"), *Base, Suffix);
		}
		UsedIds.Add(Candidate);
		return Candidate;
	}
}

TArray<FString> UMaterialCompileDiagnosticsBridge::CompileWithDiagnostics(
	UObject* MaterialOrFunction)
{
	TArray<UMaterial*> MaterialsToCompile;
	if (UMaterial* Material = Cast<UMaterial>(MaterialOrFunction))
	{
		MaterialsToCompile.Add(Material);
	}
	else if (UMaterialFunction* Function = Cast<UMaterialFunction>(MaterialOrFunction))
	{
		UMaterialEditingLibrary::UpdateMaterialFunction(Function);
		for (const FAssetData& AssetData : GetReferencingMaterials(Function))
		{
			if (UMaterial* ReferencingMaterial =
					Cast<UMaterial>(AssetData.GetAsset()))
			{
				MaterialsToCompile.AddUnique(ReferencingMaterial);
			}
		}
	}
	else
	{
		return {TEXT("Expected a Material or MaterialFunction.")};
	}

	for (UMaterial* Material : MaterialsToCompile)
	{
		UMaterialEditingLibrary::RecompileMaterial(Material);
	}
	if (GShaderCompilingManager)
	{
		GShaderCompilingManager->FinishAllCompilation();
	}

	TArray<FString> Errors;
	for (const UMaterial* Material : MaterialsToCompile)
	{
		const FMaterialResource* Resource =
			Material->GetMaterialResource(GMaxRHIShaderPlatform);
		if (!Resource)
		{
			Errors.Add(FString::Printf(
				TEXT("%s: Material compilation produced no resource for the active shader platform."),
				*Material->GetPathName()));
			continue;
		}
		for (const FString& Error : Resource->GetCompileErrors())
		{
			Errors.Add(FString::Printf(
				TEXT("%s: %s"),
				*Material->GetPathName(),
				*Error));
		}
	}
	return Errors;
}

FString UMaterialCompileDiagnosticsBridge::ExportGraphDsl(UObject* MaterialOrFunction)
{
	UMaterial* Material = Cast<UMaterial>(MaterialOrFunction);
	UMaterialFunction* Function = Cast<UMaterialFunction>(MaterialOrFunction);
	if (!Material && !Function)
	{
		return TEXT("{\"success\":false,\"errors\":[\"Expected a Material or MaterialFunction.\"]}");
	}

	const TArray<UMaterialExpression*> Expressions = GetExpressions(MaterialOrFunction);
	TMap<const UMaterialExpression*, FString> NodeIds;
	TSet<FString> UsedNodeIds;
	for (const UMaterialExpression* Expression : Expressions)
	{
		if (Expression)
		{
			NodeIds.Add(Expression, MakeSemanticNodeId(Expression, UsedNodeIds));
		}
	}

	TArray<TSharedPtr<FJsonValue>> Nodes;
	for (const UMaterialExpression* Expression : Expressions)
	{
		if (!Expression)
		{
			continue;
		}

		TSharedPtr<FJsonObject> Node = MakeShared<FJsonObject>();
		Node->SetStringField(TEXT("id"), NodeIds[Expression]);
		Node->SetStringField(
			TEXT("guid"),
			GuidToDsl(
				const_cast<UMaterialExpression*>(Expression)
					->GetMaterialExpressionId()));
		Node->SetStringField(TEXT("class"), Expression->GetClass()->GetPathName());
		Node->SetNumberField(TEXT("x"), Expression->MaterialExpressionEditorX);
		Node->SetNumberField(TEXT("y"), Expression->MaterialExpressionEditorY);
		Node->SetObjectField(TEXT("properties"), ReadEditableProperties(Expression));

		if (const UMaterialExpressionFunctionInput* Input =
				Cast<UMaterialExpressionFunctionInput>(Expression))
		{
			Node->SetStringField(TEXT("interface_guid"), GuidToDsl(Input->Id));
		}
		else if (const UMaterialExpressionFunctionOutput* Output =
					 Cast<UMaterialExpressionFunctionOutput>(Expression))
		{
			Node->SetStringField(TEXT("interface_guid"), GuidToDsl(Output->Id));
		}
		if (Expression->bIsParameterExpression)
		{
			Node->SetStringField(
				TEXT("parameter_guid"),
				GuidToDsl(
					const_cast<UMaterialExpression*>(Expression)
						->GetParameterExpressionId()));
		}
		if (const UMaterialExpressionCustom* Custom =
				Cast<UMaterialExpressionCustom>(Expression))
		{
			TSharedPtr<FJsonObject> Pins = MakeShared<FJsonObject>();
			TArray<TSharedPtr<FJsonValue>> Inputs;
			for (const FCustomInput& Input : Custom->Inputs)
			{
				Inputs.Add(MakeShared<FJsonValueString>(Input.InputName.ToString()));
			}

			TArray<TSharedPtr<FJsonValue>> Outputs;
			const UEnum* OutputTypeEnum = StaticEnum<ECustomMaterialOutputType>();
			for (const FCustomOutput& Output : Custom->AdditionalOutputs)
			{
				TSharedPtr<FJsonObject> OutputObject = MakeShared<FJsonObject>();
				OutputObject->SetStringField(
					TEXT("name"),
					Output.OutputName.ToString());
				OutputObject->SetStringField(
					TEXT("type"),
					OutputTypeEnum->GetNameStringByValue(Output.OutputType));
				Outputs.Add(MakeShared<FJsonValueObject>(OutputObject));
			}
			Pins->SetArrayField(TEXT("inputs"), Inputs);
			Pins->SetArrayField(TEXT("outputs"), Outputs);
			Node->SetObjectField(TEXT("pins"), Pins);
		}
		Nodes.Add(MakeShared<FJsonValueObject>(Node));
	}

	TArray<TSharedPtr<FJsonValue>> Connections;
	for (const UMaterialExpression* Destination : Expressions)
	{
		if (!Destination)
		{
			continue;
		}
		const TArray<FString> InputNames =
			UMaterialEditingLibrary::GetMaterialExpressionInputNames(
				const_cast<UMaterialExpression*>(Destination));
		int32 InputIndex = 0;
		for (const FExpressionInput* Input :
			 const_cast<UMaterialExpression*>(Destination)->GetInputsView())
		{
			if (Input && Input->Expression && NodeIds.Contains(Input->Expression))
			{
				TSharedPtr<FJsonObject> Edge = MakeShared<FJsonObject>();
				Edge->SetStringField(TEXT("from"), NodeIds[Input->Expression]);
				Edge->SetStringField(
					TEXT("output"),
					GetOutputName(Input->Expression, Input->OutputIndex));
				Edge->SetStringField(TEXT("to"), NodeIds[Destination]);
				const FString InputName = InputNames.IsValidIndex(InputIndex)
					? InputNames[InputIndex]
					: Input->InputName.ToString();
				Edge->SetStringField(
					TEXT("input"),
					InputName == TEXT("None") ? TEXT("") : InputName);
				Connections.Add(MakeShared<FJsonValueObject>(Edge));
			}
			++InputIndex;
		}
	}

	TArray<TSharedPtr<FJsonValue>> Outputs;
	if (Material)
	{
		const UEnum* PropertyEnum = StaticEnum<EMaterialProperty>();
		for (int32 PropertyIndex = 0; PropertyIndex < MP_MAX; ++PropertyIndex)
		{
			const EMaterialProperty Property =
				static_cast<EMaterialProperty>(PropertyIndex);
			const FExpressionInput* Input =
				Material->GetExpressionInputForProperty(Property);
			if (!Input || !Input->Expression || !NodeIds.Contains(Input->Expression))
			{
				continue;
			}

			TSharedPtr<FJsonObject> Output = MakeShared<FJsonObject>();
			Output->SetStringField(TEXT("from"), NodeIds[Input->Expression]);
			Output->SetStringField(
				TEXT("output"),
				GetOutputName(Input->Expression, Input->OutputIndex));
			Output->SetStringField(
				TEXT("property"),
				ToPythonEnumName(
					PropertyEnum->GetNameStringByValue(PropertyIndex)));
			Outputs.Add(MakeShared<FJsonValueObject>(Output));
		}
	}

	TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
	Root->SetNumberField(TEXT("version"), 3);
	Root->SetStringField(TEXT("mode"), TEXT("replace"));
	Root->SetArrayField(TEXT("nodes"), Nodes);
	Root->SetArrayField(TEXT("connections"), Connections);
	Root->SetArrayField(TEXT("outputs"), Outputs);
	Root->SetBoolField(TEXT("layout"), false);

	FString Result;
	const TSharedRef<TJsonWriter<>> Writer =
		TJsonWriterFactory<>::Create(&Result);
	FJsonSerializer::Serialize(Root.ToSharedRef(), Writer);
	return Result;
}

int32 UMaterialCompileDiagnosticsBridge::ClearGraph(UObject* MaterialOrFunction)
{
	const TArray<UMaterialExpression*> Expressions = GetExpressions(MaterialOrFunction);
	if (UMaterial* Material = Cast<UMaterial>(MaterialOrFunction))
	{
		for (int32 Index = Expressions.Num() - 1; Index >= 0; --Index)
		{
			UMaterialEditingLibrary::DeleteMaterialExpression(
				Material,
				Expressions[Index]);
		}
		Material->MarkPackageDirty();
	}
	else if (UMaterialFunction* Function =
				 Cast<UMaterialFunction>(MaterialOrFunction))
	{
		for (int32 Index = Expressions.Num() - 1; Index >= 0; --Index)
		{
			UMaterialEditingLibrary::DeleteMaterialExpressionInFunction(
				Function,
				Expressions[Index]);
		}
		Function->MarkPackageDirty();
	}
	else
	{
		return 0;
	}
	return Expressions.Num();
}

UMaterialExpression* UMaterialCompileDiagnosticsBridge::FindExpressionByGuid(
	UObject* MaterialOrFunction,
	const FString& Guid)
{
	FGuid ParsedGuid;
	if (!FGuid::Parse(Guid, ParsedGuid))
	{
		return nullptr;
	}
	for (UMaterialExpression* Expression : GetExpressions(MaterialOrFunction))
	{
		if (Expression && Expression->GetMaterialExpressionId() == ParsedGuid)
		{
			return Expression;
		}
	}
	return nullptr;
}

bool UMaterialCompileDiagnosticsBridge::SetExpressionIdentity(
	UMaterialExpression* Expression,
	const FString& NodeGuid,
	const FString& InterfaceGuid,
	const FString& ParameterGuid)
{
	if (!Expression)
	{
		return false;
	}

	FGuid ParsedGuid;
	if (!FGuid::Parse(NodeGuid, ParsedGuid))
	{
		return false;
	}
	Expression->GetMaterialExpressionId() = ParsedGuid;

	if (!InterfaceGuid.IsEmpty())
	{
		if (!FGuid::Parse(InterfaceGuid, ParsedGuid))
		{
			return false;
		}
		if (UMaterialExpressionFunctionInput* Input =
				Cast<UMaterialExpressionFunctionInput>(Expression))
		{
			Input->Id = ParsedGuid;
		}
		else if (UMaterialExpressionFunctionOutput* Output =
					 Cast<UMaterialExpressionFunctionOutput>(Expression))
		{
			Output->Id = ParsedGuid;
		}
		else
		{
			return false;
		}
	}

	if (!ParameterGuid.IsEmpty())
	{
		if (!Expression->bIsParameterExpression ||
			!FGuid::Parse(ParameterGuid, ParsedGuid))
		{
			return false;
		}
		Expression->GetParameterExpressionId() = ParsedGuid;
	}
	Expression->Modify();
	Expression->MarkPackageDirty();
	return true;
}

bool UMaterialCompileDiagnosticsBridge::ConfigureCustomPins(
	UMaterialExpression* Expression,
	const TArray<FString>& InputNames,
	const TArray<FString>& OutputNames,
	const TArray<FString>& OutputTypes)
{
	UMaterialExpressionCustom* Custom =
		Cast<UMaterialExpressionCustom>(Expression);
	if (!Custom || OutputNames.Num() != OutputTypes.Num())
	{
		return false;
	}

	Custom->Modify();
	Custom->Inputs.Reset(InputNames.Num());
	for (const FString& InputName : InputNames)
	{
		FCustomInput& Input = Custom->Inputs.AddDefaulted_GetRef();
		Input.InputName = FName(*InputName);
	}

	const UEnum* OutputTypeEnum = StaticEnum<ECustomMaterialOutputType>();
	Custom->AdditionalOutputs.Reset(OutputNames.Num());
	for (int32 Index = 0; Index < OutputNames.Num(); ++Index)
	{
		const int64 OutputType =
			OutputTypeEnum->GetValueByNameString(OutputTypes[Index]);
		if (OutputType == INDEX_NONE || OutputType == CMOT_MAX)
		{
			return false;
		}
		FCustomOutput& Output = Custom->AdditionalOutputs.AddDefaulted_GetRef();
		Output.OutputName = FName(*OutputNames[Index]);
		Output.OutputType =
			static_cast<ECustomMaterialOutputType>(OutputType);
	}
	Custom->RebuildOutputs();
	Custom->MarkPackageDirty();
	return true;
}

bool UMaterialCompileDiagnosticsBridge::DisconnectExpressionInput(
	UMaterialExpression* Expression,
	const FString& InputName)
{
	if (!Expression)
	{
		return false;
	}

	const TArray<FString> InputNames =
		UMaterialEditingLibrary::GetMaterialExpressionInputNames(Expression);
	int32 Index = 0;
	for (FExpressionInput* Input : Expression->GetInputsView())
	{
		const FString CurrentName = InputNames.IsValidIndex(Index)
			? InputNames[Index]
			: Input->InputName.ToString();
		if ((InputName.IsEmpty() &&
			 (CurrentName.IsEmpty() || CurrentName == TEXT("None"))) ||
			CurrentName == InputName)
		{
			Input->Expression = nullptr;
			Expression->Modify();
			Expression->MarkPackageDirty();
			return true;
		}
		++Index;
	}
	return false;
}

bool UMaterialCompileDiagnosticsBridge::DisconnectMaterialOutput(
	UMaterial* Material,
	const EMaterialProperty MaterialProperty)
{
	if (!Material)
	{
		return false;
	}
	FExpressionInput* Input =
		Material->GetExpressionInputForProperty(MaterialProperty);
	if (!Input)
	{
		return false;
	}
	Input->Expression = nullptr;
	Material->Modify();
	Material->MarkPackageDirty();
	return true;
}
