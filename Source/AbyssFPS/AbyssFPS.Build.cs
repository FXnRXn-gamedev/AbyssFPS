// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AbyssFPS : ModuleRules
{
	public AbyssFPS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		IWYUSupport = IWYUSupport.Full;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput",
			"UMG",
			"Slate",
			"SlateCore",
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks",
			"AIModule",
			"NavigationSystem",
			"Niagara",
			"PhysicsCore",
			"NetCore"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"OnlineSubsystem",
			"OnlineSubsystemSteam",
			"OnlineSubsystemUtils"
		});
		
		// Enable exceptions for online subsystem
		bEnableExceptions = true;
		
		// Optimization
		OptimizeCode = CodeOptimization.InShippingBuildsOnly;
		
		// Enable hot reloading
		bUseUnity = false;
		


		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
