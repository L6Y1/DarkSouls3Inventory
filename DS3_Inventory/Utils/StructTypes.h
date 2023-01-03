// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "StructTypes.generated.h"

/**
 * 
 */
UCLASS()
class DS3_INVENTORY_API UStructTypes : public UObject
{
	GENERATED_BODY()
	
};


UENUM(BlueprintType)
enum ItemClassification { ENUM_START, Consumables = ENUM_START, Equipment, Important, Keys, Rings, Arrows, ENUM_END };

// #define IntToClassification(num) static_cast<ItemClassification>(num)

USTRUCT(BlueprintType)
struct FSortCardsType1Attr : public FTableRowBase
{
	GENERATED_BODY()

public:
	FSortCardsType1Attr() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D SortCardsSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D CardContainerSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName LeftButtonImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName RightButtonImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SortCardType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SortCardNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TEnumAsByte<ItemClassification>, FName> CardImage;
};


USTRUCT(BlueprintType)
struct FInventoryType1Attr : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	FInventoryType1Attr() {}

	// size of the full inventory widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D InventorySize;

	// size of the inventory item background image
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D InventoryBaseImageSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName InventoryBaseImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SortCardWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemGridWidgetClass;
};


USTRUCT(BlueprintType)
struct FNavButtonAttr : public FTableRowBase
{
	GENERATED_BODY()

public:
	FNavButtonAttr() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ButtonLayoutStyle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D ButtonSize;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ButtonImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName HoveredImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ToggledFullScreenWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> ToggledFullScreenWidgetPartsClass;
	
	
	
};


USTRUCT(BlueprintType)
struct FMenuTopType1Attr : public FTableRowBase
{
	GENERATED_BODY()

public:
	FMenuTopType1Attr() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D WidgetSize;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MenuTopBackGroundImg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MenuSelectImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemSelectImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NavButtonType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName QuickBarType;

	
};

USTRUCT(BlueprintType)
struct FFullScreenDisplayType1Attr : public FTableRowBase
{
	GENERATED_BODY()

public:
	FFullScreenDisplayType1Attr() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TitleBGImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D TitleImageSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TitleImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TitleText;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName FooterBGImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MenuBaseImage;
};
