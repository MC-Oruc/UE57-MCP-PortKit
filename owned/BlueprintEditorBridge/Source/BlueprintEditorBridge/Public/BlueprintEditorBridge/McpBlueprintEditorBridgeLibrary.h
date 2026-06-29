#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "BlueprintEditorBridge/McpBlueprintGraphPin.h"
#include "McpBlueprintEditorBridgeLibrary.generated.h"

class UBlueprint;
class UEdGraph;
class UK2Node;

UCLASS()
class BLUEPRINTEDITORBRIDGE_API UMcpBlueprintEditorBridgeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Blueprint Editor")
	static TArray<UEdGraph*> ListGraphs(UBlueprint* Blueprint);

	UFUNCTION(BlueprintCallable, Category = "Blueprint Editor")
	static void ListGraphNames(const UBlueprint* Blueprint, TArray<FName>& OutGraphNames);

	UFUNCTION(BlueprintCallable, Category = "Blueprint Editor")
	static void ListMemberVariableNames(const UBlueprint* Blueprint, TArray<FString>& OutMemberVariableNames, bool bIncludeInheritedMembers = true);

	UFUNCTION(BlueprintCallable, Category = "Blueprint Editor")
	static FString GetBlueprintVariableCategory(UBlueprint* Blueprint, FName VariableName);

	UFUNCTION(BlueprintCallable, Category = "Blueprint Editor")
	static void SetBlueprintVariableCategory(UBlueprint* Blueprint, FName VariableName, const FString& Category);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Blueprint Editor")
	static UClass* GetBlueprintParentClass(const UBlueprint* Blueprint);

	UFUNCTION(BlueprintCallable, Category = "Blueprint Graph Editing", meta = (ScriptMethod))
	static TArray<FMcpBlueprintGraphPin> ListAllPins(const UK2Node* Node, TEnumAsByte<EEdGraphPinDirection> InDirection = EEdGraphPinDirection::EGPD_MAX);

	UFUNCTION(BlueprintCallable, Category = "Blueprint Graph Editing", meta = (ScriptMethod))
	static TArray<FMcpBlueprintGraphPin> ListInputPins(const UK2Node* Node);

	UFUNCTION(BlueprintCallable, Category = "Blueprint Graph Editing", meta = (ScriptMethod))
	static TArray<FMcpBlueprintGraphPin> ListOutputPins(const UK2Node* Node);

	UFUNCTION(BlueprintCallable, Category = "Blueprint Graph Editing", meta = (ScriptMethod))
	static void SetNodePos(UK2Node* Node, FIntPoint Pos);

	UFUNCTION(BlueprintCallable, Category = "Blueprint Graph Editing", meta = (ScriptMethod))
	static FIntPoint GetNodePos(const UK2Node* Node);

	UFUNCTION(BlueprintCallable, Category = "Blueprint Graph Editing", meta = (ScriptMethod))
	static FString GetNodeTitle(const UK2Node* Node);

	UFUNCTION(BlueprintCallable, Category = "Blueprint Graph Editing", meta = (ScriptMethod))
	static FString GetNodeCategory(const UK2Node* Node);
};
