// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BattleSphereLegends : ModuleRules
{
	public BattleSphereLegends(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput","OnlineSubsystem", "OnlineSubsystemUtils", "OnlineSubsystemEOS" });
	}
}
