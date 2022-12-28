// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DS3_Inventory/Utils/UIManager/UIState.h"
#include "UMG/Public/Blueprint/UserWidget.h"
#include "MainUI.generated.h"

/**
 * 
 */
UCLASS()
class DS3_INVENTORY_API UMainUI : public UUIState
{
	GENERATED_BODY()

private:

	
public:
	// widgets
	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UNamedSlot *MenuTopSlot;
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;




	UFUNCTION()
	void Init();

	UFUNCTION()
	void ToggleMenuTop();
};
