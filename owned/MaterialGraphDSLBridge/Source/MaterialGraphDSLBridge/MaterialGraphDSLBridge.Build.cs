using UnrealBuildTool;

public class MaterialGraphDSLBridge : ModuleRules
{
	public MaterialGraphDSLBridge(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new[]
			{
				"Core",
				"CoreUObject",
				"Engine"
			});

		PrivateDependencyModuleNames.AddRange(
			new[]
			{
				"AssetRegistry",
				"EditorScriptingUtilities",
				"Json",
				"MaterialEditor",
				"RenderCore",
				"RHI",
				"ToolsetRegistry",
				"UnrealEd"
			});
	}
}
