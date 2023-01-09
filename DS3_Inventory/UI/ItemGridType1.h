// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "ItemGridType1.generated.h"


class UTextBlock;
class UImage;
class USizeBox;
/**
 * 
 */
UCLASS()
class DS3_INVENTORY_API UItemGridType1 : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
private:
	int CurrentItemIndex;
	int ItemID;
	FName ItemName;

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
	
	// IUserObjectListEntry implementation
	virtual void NativeOnListItemObjectSet(UObject *ListItemObject) override;
	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;
	
	
public:
	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	USizeBox *ItemGridSizeBox;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UImage *ItemGridBaseImage;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	USizeBox *DishImageSizeBox;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UImage *DishImage;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	USizeBox *ItemImageSizeBox;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UImage *ItemImage;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UTextBlock *ItemNumText;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UImage *SelectImage;

	

public:
	// UFUNCTION()
	// void Init();
	
};
