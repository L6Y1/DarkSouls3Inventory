// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PickupTipType1.generated.h"

class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class DS3_INVENTORY_API UPickupTipType1 : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UImage *PickupBaseImage;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UImage *ItemImage;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UTextBlock *ItemNameText;
	
	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UTextBlock *ItemNumText;

public:

	virtual void NativeConstruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry &InGeometry, const FKeyEvent &InKeyEvent) override;
	
	UFUNCTION()
	void Init(FName ItemName, FName ItemImageName, int Num);
};
