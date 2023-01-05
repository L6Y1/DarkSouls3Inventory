// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class DS3_InventoryTarget : TargetRules
{
	public DS3_InventoryTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("DS3_Inventory");
		WindowsPlatform.PCHMemoryAllocationFactor = 2000;
	}
}
