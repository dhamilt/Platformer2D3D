// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Platformer2D3D : ModuleRules
{
	public Platformer2D3D(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
