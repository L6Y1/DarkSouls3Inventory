// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DS3_Inventory/Utils/StructTypes.h"
#include "DataTableTool.generated.h"

class UDataTable;
/**
 * 
 */
UCLASS()
class DS3_INVENTORY_API UDataTableTool : public UObject
{
	GENERATED_BODY()
	
};

class FDataTableTool
{
	
private:
	static UDataTable *DT_MenuTopType1Attr;
	static UDataTable *DT_NavButtonAttr;
	static UDataTable *DT_FullScreenDisplayType1Attr;
	static UDataTable *DT_InventoryType1Attr;
	static UDataTable *DT_SortCardsType1Attr;
	
public:
	static FMenuTopType1Attr *GetMenuTopType1Attr(FName RowName);
	static FNavButtonAttr *GetNavButtonAttr(FName RowName);
	static FFullScreenDisplayType1Attr *GetFullScreenDisplayType1Attr(FName RowName);
	static FInventoryType1Attr *GetInventoryType1Attr(FName RowName);
	static FSortCardsType1Attr *GetSortCardsType1Attr(FName RowName);
};
