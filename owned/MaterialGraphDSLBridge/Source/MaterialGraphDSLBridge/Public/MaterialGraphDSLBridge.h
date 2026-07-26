#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SceneTypes.h"

#include "MaterialGraphDSLBridge.generated.h"

class UMaterial;
class UMaterialExpression;

USTRUCT(BlueprintType)
struct MATERIALGRAPHDSLBRIDGE_API FMaterialGraphCommentInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Material Graph DSL")
	FString NodeId;

	UPROPERTY(BlueprintReadOnly, Category = "Material Graph DSL")
	FString Guid;

	UPROPERTY(BlueprintReadOnly, Category = "Material Graph DSL")
	FString Text;

	UPROPERTY(BlueprintReadOnly, Category = "Material Graph DSL")
	int32 X = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Material Graph DSL")
	int32 Y = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Material Graph DSL")
	int32 SizeX = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Material Graph DSL")
	int32 SizeY = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Material Graph DSL")
	int32 FontSize = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Material Graph DSL")
	float ColorR = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Material Graph DSL")
	float ColorG = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Material Graph DSL")
	float ColorB = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Material Graph DSL")
	float ColorA = 0.0f;
};

UCLASS()
class MATERIALGRAPHDSLBRIDGE_API UMaterialCompileDiagnosticsBridge final
	: public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Material Graph DSL")
	static TArray<FString> CompileWithDiagnostics(UObject* MaterialOrFunction);
};

UCLASS()
class MATERIALGRAPHDSLBRIDGE_API UMaterialGraphDSLBridge final
	: public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Material Graph DSL")
	static FString ExportGraphDsl(UObject* MaterialOrFunction);

	UFUNCTION(BlueprintCallable, Category = "Material Graph DSL")
	static TArray<UMaterialExpression*> GetExpressionsAndComments(
		UObject* MaterialOrFunction);

	UFUNCTION(BlueprintCallable, Category = "Material Graph DSL")
	static TArray<FMaterialGraphCommentInfo> GetGraphComments(
		UObject* MaterialOrFunction);

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

	UFUNCTION(BlueprintCallable, Category = "Material Graph DSL")
	static class UMaterialExpressionComment* CreateMaterialComment(
		UObject* MaterialOrFunction,
		int32 NodePosX,
		int32 NodePosY);

	UFUNCTION(BlueprintCallable, Category = "Material Graph DSL")
	static bool DeleteMaterialComment(
		UObject* MaterialOrFunction,
		class UMaterialExpressionComment* Comment);

	UFUNCTION(BlueprintCallable, Category = "Material Graph DSL")
	static bool SetMaterialCommentProperties(
		class UMaterialExpressionComment* Comment,
		const FString& PropertiesJson);
};
