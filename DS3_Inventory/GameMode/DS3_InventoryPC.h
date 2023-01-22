// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DS3_InventoryPC.generated.h"

class UUIManagerComponent;
/**
 * 
 */
UCLASS()
class DS3_INVENTORY_API ADS3_InventoryPC : public APlayerController
{
	GENERATED_BODY()

private:
	


	ADS3_InventoryPC();

public:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UClass *MainUIClass;
	UUserWidget *MainUIWidget;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UUIManagerComponent * UIManagerComponent;
	
	void ToggleMenuTop();
	void ReturnToFormerUI();
	void ReturnToMainUI();



};
