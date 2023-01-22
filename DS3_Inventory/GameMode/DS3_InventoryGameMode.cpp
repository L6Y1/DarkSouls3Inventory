// Copyright Epic Games, Inc. All Rights Reserved.

#include "DS3_InventoryGameMode.h"

#include "DS3_InventoryPC.h"
#include "DS3_Inventory/Utils/DataAssetMananger/DataAssetMananger.h"
#include "DS3_Inventory/Utils/DataTableTool/DataTableTool.h"
#include "DS3_Inventory/Utils/FileTool/FileTool.h"
#include "DS3_Inventory/Utils/GlobalEventManager/GlobalEventManager.h"
#include "Kismet/GameplayStatics.h"
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

void ADS3_InventoryGameMode::BeginPlay()
{
	Super::BeginPlay();

	FGlobalEventManager::RegisterEvent(FName("EndPickupItemEvent"), this, FName("EndPickupItem"));

	auto ItemOnGroundDatas = FGameSaveTool::GetItemOnGroundDatas();
	for (auto KeyValuePair : ItemOnGroundDatas)
	{
		auto ItemOnGroundData = KeyValuePair.Value;
		auto ItemOnGroundAttr = FDataTableTool::GetItemOnGroundAttr(IntToName(ItemOnGroundData.ID));

		auto ItemOnGroundClass = ADataAssetMananger::RequestSyncLoadClass(this, ItemOnGroundAttr->ActorClass);
		check(ItemOnGroundClass);

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(ItemOnGroundData.Location);
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		auto ItemOnGround = GetWorld()->SpawnActor<AActor>(ItemOnGroundClass, SpawnTransform, Params);

		auto InitFuncPtr = ItemOnGround->FindFunction(FName("Init"));
		if (InitFuncPtr)
		{
			ItemOnGround->ProcessEvent(InitFuncPtr, &ItemOnGroundData.ItemOnGroundIndex);
		}
	}
}

void ADS3_InventoryGameMode::EndPickupItem(int Remain, FName Index, FVector Location)
{
	if (Remain > 0)
	{
		// refresh the data
		auto ItemOnGroundData = FGameSaveTool::GetItemOnGroundDataByIndex(Index);
		ItemOnGroundData.Location = Location;
		ItemOnGroundData.Num = Remain;

		FGameSaveTool::SetItemOnGroundDataByIndex(Index, ItemOnGroundData);
	}
	else
	{
		// remove the data
		FGameSaveTool::RemoveItemOnGroundDataByIndex(Index);
	}
	// alert the specific item-on-ground to update itself
	FGlobalEventManager::TriggerEvent(FName("UpdateItemOnGroundEvent"), &Index);
}
