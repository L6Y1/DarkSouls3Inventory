// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DescriptionType1.generated.h"

class URichTextBlock;
class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class DS3_INVENTORY_API UDescriptionType1 : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
public:
	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UTextBlock *ItemNameText;

	UPROPERTY(meta=(BindWidget, MultiLine), VisibleAnywhere, BlueprintReadOnly)
	UTextBlock *DescriptionText0;
	
	
	UPROPERTY(meta=(BindWidget, MultiLine), VisibleAnywhere, BlueprintReadOnly)
	UTextBlock *DescriptionText1;
	
	
	UPROPERTY(meta=(BindWidget, MultiLine), VisibleAnywhere, BlueprintReadOnly)
	UTextBlock *DescriptionText2;
	
	
	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UImage *ItemImage;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UImage *DishImage;

public:
	UFUNCTION()
	void Init(FName ItemImageName, FName ItemName, int ItemID);
};
