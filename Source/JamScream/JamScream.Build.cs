using UnrealBuildTool;

public class JamScream : ModuleRules
{
	public JamScream(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Module_Menu_Main", "UMG" });
	}
}
