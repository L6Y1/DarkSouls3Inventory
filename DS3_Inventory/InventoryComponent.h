// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DS3_Inventory/Utils/StructTypes.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DS3_INVENTORY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	
	UFUNCTION(BlueprintCallable)
	int AddItemToInventory(int ItemID, int Amount);

	UFUNCTION()
	int AddItemToStorage(int ItemID, int Amount);

	UFUNCTION()
	void SubItem(int ItemID, int Amount);

	UFUNCTION()
	void StartPickupItem(AActor *User, FName Index);
	
	/**
	 * @brief 
	 * @param ItemID the ID of the item to be found
	 * @param OutIndex if found, the index of the item with given ID
	 * @param OutGridData if found, the GridData of given ID 
	 * @return true if inventory has this item
	 */
	bool TryFindItemIndex(int ItemID, int &OutIndex, FGridData &OutGridData);

	bool TryFindStorageItemIndex(int ItemID, int &OutIndex, FGridData &OutGridData);
};
