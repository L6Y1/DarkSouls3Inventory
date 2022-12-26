// Copyright Epic Games, Inc. All Rights Reserved.

#include "DS3_InventoryGameMode.h"

#include "DS3_InventoryPC.h"
#include "UObject/ConstructorHelpers.h"

ADS3_InventoryGameMode::ADS3_InventoryGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PlayerControllerClass = ADS3_InventoryPC::StaticClass();
}
