// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DS3_Inventory/Utils/UIManager/UIState.h"
#include "NavButton.generated.h"

class UTextBlock;
class USizeBox;
class UImage;
class UButton;
/**
 * 
 */
UCLASS()
class DS3_INVENTORY_API UNavButton : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct() override;
	
public:
	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	USizeBox *NavButtonSizeBox;
	
	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	UButton *NavButton;

	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	UImage *HoveredImage;




public:
	UFUNCTION()
	void ToggleHoveredPic();

	UFUNCTION()
	void Init();
};