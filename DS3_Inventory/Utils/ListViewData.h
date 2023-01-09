// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DS3_Inventory/Utils/StructTypes.h"
#include "UObject/NoExportTypes.h"
#include "ListViewData.generated.h"

/**
 * 
 */
UCLASS()
class DS3_INVENTORY_API UListViewData : public UObject
{
	GENERATED_BODY()
	
public:
	UListViewData() = default;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EItemClassification> ItemClassification;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemGridType1Attr ItemGridAttr;
};
