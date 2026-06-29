using UnrealBuildTool;

public class BlueprintEditorBridge : ModuleRules
{
	public BlueprintEditorBridge(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicDependencyModuleNames.AddRange(
			new[]
			{
				"Core",
				"BlueprintGraph"
			});

		PrivateDependencyModuleNames.AddRange(
			new[]
			{
				"AnimGraph",
				"BlueprintEditorLibrary",
				"CoreUObject",
				"Engine",
				"Json",
				"JsonUtilities",
				"KismetCompiler",
				"UnrealEd"
			});
	}
}
