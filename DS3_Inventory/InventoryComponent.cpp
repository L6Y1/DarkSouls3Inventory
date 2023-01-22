// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "Utils/DataTableTool/DataTableTool.h"
#include "Utils/FileTool/FileTool.h"
#include "Utils/GlobalEventManager/GlobalEventManager.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	FGlobalEventManager::RegisterEvent(FName("StartPickupItemEvent"), this, FName("StartPickupItem"));
	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int UInventoryComponent::AddItemToInventory(int ItemID, int Amount)
{
	auto ItemAttr = FDataTableTool::GetInventoryItemAttrByID(ItemID);

	int OutIndex = -1;
	FGridData OutGridData;

	TryFindItemIndex(ItemID, OutIndex, OutGridData);
	if (OutGridData.Num + Amount < ItemAttr->MaxStackNum)
	{
		OutGridData.Num += Amount;
		FGameSaveTool::SaveGrid(OutIndex, OutGridData);

		struct 
		{
			int Index;
			TEnumAsByte<EItemClassification> Classification;
			
		} Params;
		Params.Index = OutIndex;
		Params.Classification = TEnumAsByte<EItemClassification>(ItemID / 10000 - 1);
		FGlobalEventManager::TriggerEvent(FName("ItemDataChangeEvent"), &Params);
	}
	else
	{
		auto GridNum = OutGridData.Num;
		OutGridData.Num = ItemAttr->MaxStackNum;
		OutGridData.ItemID = ItemID;
		FGameSaveTool::SaveGrid(OutIndex, OutGridData);
		
		struct 
		{
			int Index;
			TEnumAsByte<EItemClassification> Classification;
			
		} Params;
		Params.Index = OutIndex;
		Params.Classification = TEnumAsByte<EItemClassification>(ItemID / 10000 - 1);
		FGlobalEventManager::TriggerEvent(FName("ItemDataChangeEvent"), &Params);
		
		return AddItemToStorage(ItemID, GridNum + Amount - ItemAttr->MaxStackNum);
	}
	
	return 0;
}

int UInventoryComponent::AddItemToStorage(int ItemID, int Amount)
{
	auto ItemAttr = FDataTableTool::GetInventoryItemAttrByID(ItemID);

	int OutIndex = -1;
	FGridData OutGridData;

	TryFindStorageItemIndex(ItemID, OutIndex, OutGridData);
	if (Amount + OutGridData.Num < ItemAttr->MaxStorageNum)
	{
		OutGridData.Num += Amount;
		FGameSaveTool::SaveStorageGrid(OutIndex, OutGridData);
	}
	else
	{
		OutGridData.Num = ItemAttr->MaxStorageNum;
		OutGridData.ItemID = ItemID;
		FGameSaveTool::SaveStorageGrid(OutIndex, OutGridData);
		return OutGridData.Num + Amount - ItemAttr->MaxStorageNum;
	}
	return 0;
}

void UInventoryComponent::SubItem(int ItemID, int Amount)
{
}

void UInventoryComponent::StartPickupItem(AActor *User, FName Index)
{
	if (this->GetOwner() == User)
	{
		auto ItemOnGroundData = FGameSaveTool::GetItemOnGroundDataByIndex(Index);
		int RemainAmount = AddItemToInventory(ItemOnGroundData.ID, ItemOnGroundData.Num);

		struct
		{
			int Remain;
			FName Index;
			FVector Location;
		} Params;
		Params.Remain = RemainAmount;
		Params.Index = Index;
		Params.Location = GetOwner()->GetActorLocation();

		FGlobalEventManager::TriggerEvent(FName("EndPickupItemEvent"), &Params);
	}
}

bool UInventoryComponent::TryFindItemIndex(int ItemID, int &OutIndex, FGridData &OutGridData)
{
	auto Classification = TEnumAsByte<EItemClassification>(ItemID / 10000 - 1);
	auto InventoryGridDataArray = FGameSaveTool::GetGameSaveData().PlayerData.InventoryData.GridDatas.Find(Classification)->ClassifiedGridDataArray;

	for (int i = 0; i < InventoryGridDataArray.Num(); ++i)
	{
		if (InventoryGridDataArray[i].ItemID == ItemID)
		{
			OutIndex = i;
			OutGridData = InventoryGridDataArray[i];
			return true;
		}
	}

	OutIndex = -1;
	OutGridData.Num = 0;
	OutGridData.ItemID = 0;
	return false;
}

bool UInventoryComponent::TryFindStorageItemIndex(int ItemID, int &OutIndex, FGridData &OutGridData)
{
	auto Classification = TEnumAsByte<EItemClassification>(ItemID / 10000 - 1);
	auto StorageGridDataArray = FGameSaveTool::GetGameSaveData().PlayerData.InventoryData.StorageGridDatas.Find(Classification)->ClassifiedStorageGridDataArray;

	for (int i = 0; i < StorageGridDataArray.Num(); ++i)
	{
		if (StorageGridDataArray[i].ItemID == ItemID)
		{
			OutIndex = i;
			OutGridData = StorageGridDataArray[i];
			return true;
		}
	}

	OutIndex = -1;
	OutGridData.Num = 0;
	OutGridData.ItemID = ItemID;
	return false;
}

