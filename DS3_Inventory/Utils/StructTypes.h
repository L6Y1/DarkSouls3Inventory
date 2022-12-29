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
	FName ToggledWidgetClass;
	
	
	
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