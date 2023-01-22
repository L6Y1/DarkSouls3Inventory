// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DS3_Inventory/Utils/StructTypes.h"
#include "DS3_Inventory/Utils/UIManager/UIState.h"
#include "FullScreenDisplayType1.generated.h"

class UTextBlock;
class USizeBox;
class UImage;
/**
 * 
 */
UCLASS()
class DS3_INVENTORY_API UFullScreenDisplayType1 : public UUIState
{
	GENERATED_BODY()
	
private:


public:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UImage *TitleBGImage;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	USizeBox *TitleImageSizeBox;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UImage *TitleImage;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UTextBlock *TitleText;
	
	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UImage *FooterBGImage;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UImage *MenuBaseImage;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UNamedSlot *SlotLeft;
	
	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UNamedSlot *SlotMiddle;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UNamedSlot *SlotRight;


public:
	UFUNCTION()
	void Init(FFullScreenDisplayType1Attr FullScreenDisplayType1Attr, TArray<FName> WidgetPartsClassName);

	UFUNCTION()
	void CreateDescription(FName ItemName, int ItemID);
};

