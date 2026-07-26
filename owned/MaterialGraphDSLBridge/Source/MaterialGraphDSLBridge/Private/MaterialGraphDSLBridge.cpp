#include "MaterialGraphDSLBridge.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "Dom/JsonObject.h"
#include "EdGraph/EdGraph.h"
#include "EdGraph/EdGraphNode.h"
#include "MaterialEditingLibrary.h"
#include "MaterialGraph/MaterialGraph.h"
#include "MaterialGraph/MaterialGraphNode_Comment.h"
#include "MaterialShared.h"
#include "Materials/Material.h"
#include "Materials/MaterialExpressionComment.h"
#include "Materials/MaterialExpressionCustom.h"
#include "Materials/MaterialExpressionFunctionInput.h"
#include "Materials/MaterialExpressionFunctionOutput.h"
#include "Materials/MaterialFunction.h"
#include "Policies/CondensedJsonPrintPolicy.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "ShaderCompiler.h"
#include "ToolsetRegistry/ToolsetLibrary.h"

namespace
{
	TArray<UMaterialExpression*> GetExpressions(UObject* MaterialOrFunction)
	{
		TArray<UMaterialExpression*> Result;
		if (UMaterial* Material = Cast<UMaterial>(MaterialOrFunction))
		{
			Result.Append(Material->GetExpressionCollection().Expressions);
			for (UMaterialExpressionComment* Comment : Material->GetExpressionCollection().EditorComments)
			{
				if (Comment)
				{
					Result.Add(Comment);
				}
			}
		}
		else if (UMaterialFunction* Function = Cast<UMaterialFunction>(MaterialOrFunction))
		{
			Result.Append(Function->GetExpressionCollection().Expressions);
			for (UMaterialExpressionComment* Comment : Function->GetExpressionCollection().EditorComments)
			{
				if (Comment)
				{
					Result.Add(Comment);
				}
			}
		}
		return Result;
	}

	bool NormalizeCommentCollection(
		UObject* MaterialOrFunction,
		UMaterialExpressionComment* Comment)
	{
		if (!MaterialOrFunction || !Comment)
		{
			return false;
		}

		FMaterialExpressionCollection* Collection = nullptr;
		if (UMaterial* Material = Cast<UMaterial>(MaterialOrFunction))
		{
			Collection = &Material->GetExpressionCollection();
			Comment->Material = Material;
			Comment->Function = nullptr;
		}
		else if (UMaterialFunction* Function = Cast<UMaterialFunction>(MaterialOrFunction))
		{
			Collection = &Function->GetExpressionCollection();
			Comment->Material = nullptr;
			Comment->Function = Function;
		}
		else
		{
			return false;
		}

		MaterialOrFunction->Modify();
		Collection->RemoveExpression(Comment);
		Collection->AddComment(Comment);
		return true;
	}

	UMaterialGraphNode_Comment* EnsureCommentGraphNode(
		UMaterialExpressionComment* Comment)
	{
		if (!Comment)
		{
			return nullptr;
		}
		if (UMaterialGraphNode_Comment* CommentNode =
				Cast<UMaterialGraphNode_Comment>(Comment->GraphNode))
		{
			return CommentNode;
		}

		UMaterialGraph* Graph = Comment->GraphNode
			? Cast<UMaterialGraph>(Comment->GraphNode->GetGraph())
			: nullptr;
		if (!Graph)
		{
			if (const UMaterial* Material = Cast<UMaterial>(Comment->GetOuter()))
			{
				Graph = Material->MaterialGraph;
			}
		}
		if (!Graph)
		{
			return nullptr;
		}

		if (Comment->GraphNode)
		{
			Graph->Modify();
			Graph->RemoveNode(Comment->GraphNode);
			Comment->GraphNode = nullptr;
		}
		return Graph->AddComment(Comment);
	}

	void SyncCommentGraphNode(UMaterialExpressionComment* Comment)
	{
		if (UMaterialGraphNode_Comment* CommentNode = EnsureCommentGraphNode(Comment))
		{
			CommentNode->Modify();
			CommentNode->NodePosX = Comment->MaterialExpressionEditorX;
			CommentNode->NodePosY = Comment->MaterialExpressionEditorY;
			CommentNode->NodeWidth = Comment->SizeX;
			CommentNode->NodeHeight = Comment->SizeY;
			CommentNode->NodeComment = Comment->Text;
			CommentNode->CommentColor = Comment->CommentColor;
			CommentNode->FontSize = Comment->FontSize;
			CommentNode->MoveMode = Comment->bGroupMode
				? ECommentBoxMode::GroupMovement
				: ECommentBoxMode::NoGroupMovement;
			if (UEdGraph* Graph = CommentNode->GetGraph())
			{
				Graph->NotifyGraphChanged();
			}
		}
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

		if (const UMaterialExpressionComment* Comment = Cast<UMaterialExpressionComment>(Expression))
		{
			Result->SetNumberField(TEXT("SizeX"), Comment->SizeX);
			Result->SetNumberField(TEXT("SizeY"), Comment->SizeY);
			Result->SetStringField(TEXT("Text"), Comment->Text);
			Result->SetNumberField(TEXT("FontSize"), Comment->FontSize);
			TSharedPtr<FJsonObject> ColorObj = MakeShared<FJsonObject>();
			ColorObj->SetNumberField(TEXT("r"), Comment->CommentColor.R);
			ColorObj->SetNumberField(TEXT("g"), Comment->CommentColor.G);
			ColorObj->SetNumberField(TEXT("b"), Comment->CommentColor.B);
			ColorObj->SetNumberField(TEXT("a"), Comment->CommentColor.A);
			Result->SetObjectField(TEXT("CommentColor"), ColorObj);
		}

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

TArray<UMaterialExpression*>
UMaterialGraphDSLBridge::GetExpressionsAndComments(
	UObject* MaterialOrFunction)
{
	return GetExpressions(MaterialOrFunction);
}

TArray<FMaterialGraphCommentInfo>
UMaterialGraphDSLBridge::GetGraphComments(
	UObject* MaterialOrFunction)
{
	TArray<FMaterialGraphCommentInfo> Result;
	TSet<FString> UsedNodeIds;
	for (UMaterialExpression* Expression : GetExpressions(MaterialOrFunction))
	{
		if (!Expression)
		{
			continue;
		}

		const FString NodeId = MakeSemanticNodeId(Expression, UsedNodeIds);
		const UMaterialExpressionComment* Comment =
			Cast<UMaterialExpressionComment>(Expression);
		if (!Comment)
		{
			continue;
		}

		FMaterialGraphCommentInfo& Info = Result.AddDefaulted_GetRef();
		Info.NodeId = NodeId;
		Info.Guid = GuidToDsl(
			const_cast<UMaterialExpressionComment*>(Comment)
				->GetMaterialExpressionId());
		Info.Text = Comment->Text;
		Info.X = Comment->MaterialExpressionEditorX;
		Info.Y = Comment->MaterialExpressionEditorY;
		Info.SizeX = Comment->SizeX;
		Info.SizeY = Comment->SizeY;
		Info.FontSize = Comment->FontSize;
		Info.ColorR = Comment->CommentColor.R;
		Info.ColorG = Comment->CommentColor.G;
		Info.ColorB = Comment->CommentColor.B;
		Info.ColorA = Comment->CommentColor.A;
	}
	return Result;
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

FString UMaterialGraphDSLBridge::ExportGraphDsl(UObject* MaterialOrFunction)
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
	const TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer =
		TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Result);
	FJsonSerializer::Serialize(Root.ToSharedRef(), Writer);
	return Result;
}

int32 UMaterialGraphDSLBridge::ClearGraph(UObject* MaterialOrFunction)
{
	const TArray<UMaterialExpression*> Expressions = GetExpressions(MaterialOrFunction);
	if (UMaterial* Material = Cast<UMaterial>(MaterialOrFunction))
	{
		for (int32 Index = Expressions.Num() - 1; Index >= 0; --Index)
		{
			if (UMaterialExpressionComment* Comment =
					Cast<UMaterialExpressionComment>(Expressions[Index]))
			{
				DeleteMaterialComment(Material, Comment);
			}
			else
			{
				UMaterialEditingLibrary::DeleteMaterialExpression(
					Material,
					Expressions[Index]);
			}
		}
		Material->MarkPackageDirty();
	}
	else if (UMaterialFunction* Function =
				 Cast<UMaterialFunction>(MaterialOrFunction))
	{
		for (int32 Index = Expressions.Num() - 1; Index >= 0; --Index)
		{
			if (UMaterialExpressionComment* Comment =
					Cast<UMaterialExpressionComment>(Expressions[Index]))
			{
				DeleteMaterialComment(Function, Comment);
			}
			else
			{
				UMaterialEditingLibrary::DeleteMaterialExpressionInFunction(
					Function,
					Expressions[Index]);
			}
		}
		Function->MarkPackageDirty();
	}
	else
	{
		return 0;
	}
	return Expressions.Num();
}

UMaterialExpression* UMaterialGraphDSLBridge::FindExpressionByGuid(
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

bool UMaterialGraphDSLBridge::SetExpressionIdentity(
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

bool UMaterialGraphDSLBridge::ConfigureCustomPins(
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

bool UMaterialGraphDSLBridge::DisconnectExpressionInput(
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

bool UMaterialGraphDSLBridge::DisconnectMaterialOutput(
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

UMaterialExpressionComment* UMaterialGraphDSLBridge::CreateMaterialComment(
	UObject* MaterialOrFunction,
	int32 NodePosX,
	int32 NodePosY)
{
	if (!Cast<UMaterial>(MaterialOrFunction) &&
		!Cast<UMaterialFunction>(MaterialOrFunction))
	{
		return nullptr;
	}

	MaterialOrFunction->Modify();
	UMaterialExpressionComment* NewComment =
		NewObject<UMaterialExpressionComment>(
			MaterialOrFunction,
			UMaterialExpressionComment::StaticClass(),
			NAME_None,
			RF_Transactional);
	NewComment->MaterialExpressionEditorX = NodePosX;
	NewComment->MaterialExpressionEditorY = NodePosY;
	NewComment->SizeX = 400;
	NewComment->SizeY = 100;
	NewComment->Text =
		NSLOCTEXT("MaterialGraphDSL", "DefaultCommentText", "Comment").ToString();
	NewComment->UpdateMaterialExpressionGuid(true, true);
	NormalizeCommentCollection(MaterialOrFunction, NewComment);
	SyncCommentGraphNode(NewComment);
	NewComment->MarkPackageDirty();
	MaterialOrFunction->MarkPackageDirty();

	return NewComment;
}

bool UMaterialGraphDSLBridge::DeleteMaterialComment(
	UObject* MaterialOrFunction,
	UMaterialExpressionComment* Comment)
{
	if (!MaterialOrFunction || !Comment)
	{
		return false;
	}

	FMaterialExpressionCollection* Collection = nullptr;
	if (UMaterial* Material = Cast<UMaterial>(MaterialOrFunction))
	{
		Collection = &Material->GetExpressionCollection();
	}
	else if (UMaterialFunction* Function = Cast<UMaterialFunction>(MaterialOrFunction))
	{
		Collection = &Function->GetExpressionCollection();
	}
	if (!Collection ||
		(!Collection->EditorComments.Contains(Comment) &&
		 !Collection->Expressions.Contains(Comment)))
	{
		return false;
	}

	MaterialOrFunction->Modify();
	Comment->Modify();
	if (Comment->GraphNode)
	{
		if (UEdGraph* Graph = Comment->GraphNode->GetGraph())
		{
			Graph->Modify();
			Graph->RemoveNode(Comment->GraphNode);
			Graph->NotifyGraphChanged();
		}
		Comment->GraphNode = nullptr;
	}
	Collection->RemoveExpression(Comment);
	Collection->RemoveComment(Comment);
	Comment->MarkAsGarbage();
	MaterialOrFunction->MarkPackageDirty();
	return true;
}

bool UMaterialGraphDSLBridge::SetMaterialCommentProperties(
	UMaterialExpressionComment* Comment,
	const FString& PropertiesJson)
{
	if (!Comment)
	{
		return false;
	}

	TSharedPtr<FJsonObject> Properties;
	const TSharedRef<TJsonReader<>> Reader =
		TJsonReaderFactory<>::Create(PropertiesJson);
	if (!FJsonSerializer::Deserialize(Reader, Properties) || !Properties.IsValid())
	{
		return false;
	}

	UObject* Owner = Comment->Material
		? static_cast<UObject*>(Comment->Material)
		: static_cast<UObject*>(Comment->Function);
	if (!Owner)
	{
		Owner = Comment->GetOuter();
	}
	if (!NormalizeCommentCollection(Owner, Comment))
	{
		return false;
	}

	Comment->Modify();
	for (const TPair<UE::FSharedString, TSharedPtr<FJsonValue>>& Pair :
		 Properties->Values)
	{
		FString Key = FString(*Pair.Key).ToLower();
		Key.ReplaceInline(TEXT("_"), TEXT(""));
		if (Key == TEXT("sizex") || Key == TEXT("sizey") ||
			Key == TEXT("fontsize"))
		{
			double Value = 0.0;
			if (!Pair.Value->TryGetNumber(Value))
			{
				return false;
			}
			const int32 IntegerValue = FMath::Max(1, FMath::TruncToInt(Value));
			if (Key == TEXT("sizex"))
			{
				Comment->SizeX = IntegerValue;
			}
			else if (Key == TEXT("sizey"))
			{
				Comment->SizeY = IntegerValue;
			}
			else
			{
				Comment->FontSize = IntegerValue;
			}
		}
		else if (Key == TEXT("text"))
		{
			if (!Pair.Value->TryGetString(Comment->Text))
			{
				return false;
			}
		}
		else if (Key == TEXT("commentcolor"))
		{
			const TSharedPtr<FJsonObject>* Color = nullptr;
			if (!Pair.Value->TryGetObject(Color) || !Color || !Color->IsValid())
			{
				return false;
			}
			double Channel = 0.0;
			if ((*Color)->TryGetNumberField(TEXT("r"), Channel))
			{
				Comment->CommentColor.R = static_cast<float>(Channel);
			}
			if ((*Color)->TryGetNumberField(TEXT("g"), Channel))
			{
				Comment->CommentColor.G = static_cast<float>(Channel);
			}
			if ((*Color)->TryGetNumberField(TEXT("b"), Channel))
			{
				Comment->CommentColor.B = static_cast<float>(Channel);
			}
			if ((*Color)->TryGetNumberField(TEXT("a"), Channel))
			{
				Comment->CommentColor.A = static_cast<float>(Channel);
			}
		}
		else
		{
			return false;
		}
	}

	SyncCommentGraphNode(Comment);
	Comment->PostEditChange();
	Comment->MarkPackageDirty();
	Owner->MarkPackageDirty();
	return true;
}
