#include "BlueprintEditorBridge/McpBlueprintEditorBridgeLibrary.h"

#include "BlueprintEditorBridge/McpBlueprintGraphPin.h"
#include "EdGraphSchema_K2.h"
#include "K2Node.h"
#include "Kismet2/BlueprintEditorUtils.h"

TArray<UEdGraph*> UMcpBlueprintEditorBridgeLibrary::ListGraphs(UBlueprint* Blueprint)
{
	TArray<UEdGraph*> Result;
	if (Blueprint)
	{
		Blueprint->GetAllGraphs(Result);
	}
	return Result;
}

void UMcpBlueprintEditorBridgeLibrary::ListGraphNames(const UBlueprint* Blueprint, TArray<FName>& OutGraphNames)
{
	OutGraphNames.Reset();
	if (!Blueprint)
	{
		return;
	}

	TArray<UEdGraph*> Graphs;
	const_cast<UBlueprint*>(Blueprint)->GetAllGraphs(Graphs);
	for (const UEdGraph* Graph : Graphs)
	{
		if (Graph)
		{
			OutGraphNames.Add(Graph->GetFName());
		}
	}
}

void UMcpBlueprintEditorBridgeLibrary::ListMemberVariableNames(const UBlueprint* Blueprint, TArray<FString>& OutMemberVariableNames, bool bIncludeInheritedMembers)
{
	OutMemberVariableNames.Reset();
	if (!Blueprint)
	{
		return;
	}

	for (const FBPVariableDescription& Variable : Blueprint->NewVariables)
	{
		OutMemberVariableNames.Add(Variable.VarName.ToString());
	}

	(void)bIncludeInheritedMembers;
}

FString UMcpBlueprintEditorBridgeLibrary::GetBlueprintVariableCategory(UBlueprint* Blueprint, FName VariableName)
{
	return Blueprint
		? FBlueprintEditorUtils::GetBlueprintVariableCategory(Blueprint, VariableName, nullptr).ToString()
		: FString();
}

void UMcpBlueprintEditorBridgeLibrary::SetBlueprintVariableCategory(UBlueprint* Blueprint, FName VariableName, const FString& Category)
{
	if (!Blueprint)
	{
		return;
	}

	FBlueprintEditorUtils::SetBlueprintVariableCategory(Blueprint, VariableName, nullptr, FText::FromString(Category));
}

UClass* UMcpBlueprintEditorBridgeLibrary::GetBlueprintParentClass(const UBlueprint* Blueprint)
{
	return Blueprint ? Blueprint->ParentClass : nullptr;
}

TArray<FMcpBlueprintGraphPin> UMcpBlueprintEditorBridgeLibrary::ListAllPins(const UK2Node* Node, TEnumAsByte<EEdGraphPinDirection> InDirection)
{
	TArray<FMcpBlueprintGraphPin> Result;
	if (!Node)
	{
		return Result;
	}

	for (UEdGraphPin* Pin : Node->Pins)
	{
		if (!Pin || Pin->bHidden)
		{
			continue;
		}

		if (InDirection != EEdGraphPinDirection::EGPD_MAX && Pin->Direction != InDirection)
		{
			continue;
		}

		Result.Add(UMcpBlueprintGraphPinLibrary::FromNativePin(Pin));
	}
	return Result;
}

TArray<FMcpBlueprintGraphPin> UMcpBlueprintEditorBridgeLibrary::ListInputPins(const UK2Node* Node)
{
	return ListAllPins(Node, EEdGraphPinDirection::EGPD_Input);
}

TArray<FMcpBlueprintGraphPin> UMcpBlueprintEditorBridgeLibrary::ListOutputPins(const UK2Node* Node)
{
	return ListAllPins(Node, EEdGraphPinDirection::EGPD_Output);
}

void UMcpBlueprintEditorBridgeLibrary::SetNodePos(UK2Node* Node, FIntPoint Pos)
{
	if (!Node)
	{
		return;
	}

	Node->Modify();
	Node->NodePosX = Pos.X;
	Node->NodePosY = Pos.Y;
}

FIntPoint UMcpBlueprintEditorBridgeLibrary::GetNodePos(const UK2Node* Node)
{
	return Node ? FIntPoint(Node->NodePosX, Node->NodePosY) : FIntPoint::ZeroValue;
}

FString UMcpBlueprintEditorBridgeLibrary::GetNodeTitle(const UK2Node* Node)
{
	return Node ? Node->GetNodeTitle(ENodeTitleType::ListView).ToString() : FString();
}

FString UMcpBlueprintEditorBridgeLibrary::GetNodeCategory(const UK2Node* Node)
{
	return Node ? Node->GetMenuCategory().ToString() : FString();
}
