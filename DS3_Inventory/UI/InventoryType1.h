// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DS3_Inventory/Utils/StructTypes.h"
#include "InventoryType1.generated.h"

class UWrapBox;
class UScrollBox;
class UTextBlock;
class UImage;
class USizeBox;
/**
 * 
 */
UCLASS()
class DS3_INVENTORY_API UInventoryType1 : public UUserWidget
{
	GENERATED_BODY()

private:

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:
	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	USizeBox *InventorySizeBox;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UNamedSlot *SortCardsSlot;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	USizeBox *InventoryBaseSizeBox;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UImage *InventoryBaseImage;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UTextBlock *ItemNameText;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UScrollBox *InventoryItemScrollBox;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UWrapBox *InventoryItemWrapBox;

public:
	UFUNCTION()
	void Init(FInventoryType1Attr InventoryAttr);

	virtual FReply NativeOnFocusReceived(const FGeometry &InGeometry, const FFocusEvent &InFocusEvent) override;
	virtual void NativeOnFocusLost(const FFocusEvent &InFocusEvent) override;
};
