// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class InterfaceHero : ModuleRules
{
	public InterfaceHero(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"GameplayTags",
			"UMG",
			"CommonUI",
			"DeveloperSettings",
			"CommonInput",
			"PropertyPath",
			"PreLoadScreen"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { "CommonUI", "CommonInput" });

		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
