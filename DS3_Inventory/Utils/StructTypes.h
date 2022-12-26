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
struct FNavButtonAttrs : public FTableRowBase
{
	GENERATED_BODY()

public:
	FNavButtonAttrs() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ButtonImage;
	
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
	FName NavButtonStyle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName QuickBarStyle;

	
};