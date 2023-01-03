// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DS3_Inventory/Utils/StructTypes.h"
#include "SortCard.generated.h"

class UOverlay;
class UOverlaySlot;
class UImage;
/**
 * 
 */
UCLASS()
class DS3_INVENTORY_API USortCard : public UUserWidget
{
	GENERATED_BODY()
private:
	UOverlaySlot *BGImageSlot;
	UOverlaySlot *SortImageSlot;
	UOverlaySlot *ShadderImageSlot;

	ItemClassification CardIndex;
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual void NativeOnMouseEnter(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent) override;
	
public:
	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UOverlay *SortCardOverlay;
	
	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UImage *BGImage;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UImage *SortImage;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UImage *ShadderImage;

public:
	UFUNCTION()
	void Init(TEnumAsByte<ItemClassification> Index, FName ImageName);

	UFUNCTION()
	void PopUp();

	UFUNCTION()
	void PopDown();
	
	UFUNCTION()
	void OnCardActive(TEnumAsByte<ItemClassification> Index);
};

