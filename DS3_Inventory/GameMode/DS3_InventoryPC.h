// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DS3_InventoryPC.generated.h"

/**
 * 
 */
UCLASS()
class DS3_INVENTORY_API ADS3_InventoryPC : public APlayerController
{
	GENERATED_BODY()

private:
	UClass *MainUIClass;

	UUserWidget *MainUIWidget;
	
	ADS3_InventoryPC();

public:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;


	
	void ToggleMenuTop();
};
