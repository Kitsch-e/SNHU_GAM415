// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GAM415 : ModuleRules
{
	public GAM415(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
