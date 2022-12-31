// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DS3_Inventory/Utils/StructTypes.h"
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
	FName Name;
	FNavButtonAttr SelfAttr;
	
public:
	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	USizeBox *NavButtonSizeBox;
	
	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	UButton *NavButton;

	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	UImage *HoveredImage;




public:
	virtual void NativeConstruct() override;

	
	UFUNCTION()
	void ToggleHoveredPic();

	UFUNCTION()
	void ShowMenuTopHint();
	
	UFUNCTION()
	void HideMenuTopHint();

	UFUNCTION()
	void NativeOnClick();
	
	UFUNCTION()
	void Init(FName ButtonName, FNavButtonAttr NavButtonAttr);
};