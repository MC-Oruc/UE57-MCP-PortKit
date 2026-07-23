#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SceneTypes.h"

#include "MaterialGraphDSLBridge.generated.h"

class UMaterial;
class UMaterialExpression;

UCLASS()
class MATERIALGRAPHDSLBRIDGE_API UMaterialCompileDiagnosticsBridge final
	: public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Material Graph DSL")
	static TArray<FString> CompileWithDiagnostics(UObject* MaterialOrFunction);

	UFUNCTION(BlueprintCallable, Category = "Material Graph DSL")
	static FString ExportGraphDsl(UObject* MaterialOrFunction);

	UFUNCTION(BlueprintCallable, Category = "Material Graph DSL")
	static int32 ClearGraph(UObject* MaterialOrFunction);

	UFUNCTION(BlueprintCallable, Category = "Material Graph DSL")
	static UMaterialExpression* FindExpressionByGuid(
		UObject* MaterialOrFunction,
		const FString& Guid);

	UFUNCTION(BlueprintCallable, Category = "Material Graph DSL")
	static bool SetExpressionIdentity(
		UMaterialExpression* Expression,
		const FString& NodeGuid,
		const FString& InterfaceGuid,
		const FString& ParameterGuid);

	UFUNCTION(BlueprintCallable, Category = "Material Graph DSL")
	static bool ConfigureCustomPins(
		UMaterialExpression* Expression,
		const TArray<FString>& InputNames,
		const TArray<FString>& OutputNames,
		const TArray<FString>& OutputTypes);

	UFUNCTION(BlueprintCallable, Category = "Material Graph DSL")
	static bool DisconnectExpressionInput(
		UMaterialExpression* Expression,
		const FString& InputName);

	UFUNCTION(BlueprintCallable, Category = "Material Graph DSL")
	static bool DisconnectMaterialOutput(
		UMaterial* Material,
		EMaterialProperty MaterialProperty);
};
