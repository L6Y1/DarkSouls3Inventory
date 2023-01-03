// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DS3_Inventory/Utils/StructTypes.h"
#include "SortCardsType1.generated.h"

class UImage;
class UButton;
class UHorizontalBox;
class USizeBox;
/**
 * 
 */
UCLASS()
class DS3_INVENTORY_API USortCardsType1 : public UUserWidget
{
	GENERATED_BODY()
	
private:
	// how many SortCards to display
	int CardNum;

	// enum that is currently being displayed
	TArray<TEnumAsByte<ItemClassification>> DisplayingIndex;
	// corresponding Image name for each enum
	TMap<TEnumAsByte<ItemClassification>, FName> CardImages;
	
	// the number of enums in ItemClassification
	const ItemClassification TotalNum = TEnumAsByte<ItemClassification>(ItemClassification::ENUM_END - ENUM_START);
	// current viewing classification
	ItemClassification CurrentActiveIndex = ItemClassification::ENUM_START;

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry &MyGeometry, float InDeltaTime) override;
	
public:
	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	USizeBox *SortCardsSizeBox;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	USizeBox *CardContainerSizeBox;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UHorizontalBox *SortCardsHorBox;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UButton *LeftButton;
	
	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UButton *RightButton;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UImage *LeftShadder;
	
	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UImage *RightShadder;


public:
	UFUNCTION()
	void Init(FSortCardsType1Attr SortCardsAttr);

	UFUNCTION()
	void UpdateActiveIndex(TEnumAsByte<ItemClassification> Index);

	UFUNCTION()
	void NativeLeftButtonClicked();
	
	UFUNCTION()
	void NativeRightButtonClicked();
};
