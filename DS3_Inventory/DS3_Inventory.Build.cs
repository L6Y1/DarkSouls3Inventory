// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DS3_Inventory : ModuleRules
{
	public DS3_Inventory(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay",
			"Paper2D", "SlateCore", "UMG", "Json","JsonUtilities", "interactive" });
	}
}
