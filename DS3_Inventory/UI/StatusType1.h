// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DS3_Inventory/Utils/StructTypes.h"
#include "StatusType1.generated.h"

class UImage;
class UVerticalBox;
/**
 * 
 */
UCLASS()
class DS3_INVENTORY_API UStatusType1 : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UClass *DividerStyle4Class = nullptr;
	
public:

	UFUNCTION()
	void Init(FStatusType1Attr StatusAttr);

	void CreateAndBindStatusUnit(TTuple<FString, int> Data, UClass *UnitClass);

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UVerticalBox *StatsVerticalBox;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UImage *StatusBaseImage;
};
