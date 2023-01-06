// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DS3_Inventory/Utils/StructTypes.h"
#include "DataTableTool.generated.h"

class UDataTable;


#define DataTable_Signature(Signature)\
private:\
static UDataTable *DT_##Signature##;\
public:\
static F##Signature##* Get##Signature##(FName RowName);


#define DataTable_Impl(Signature, DataTablePath)\
UDataTable* FDataTableTool::DT_##Signature## = nullptr;\
F##Signature## * FDataTableTool::Get##Signature##(FName RowName)\
{\
if (!DT_##Signature##)\
{\
DT_##Signature## = LoadObject<UDataTable>(nullptr, DataTablePath);\
check(DT_##Signature##);\
}\
\
if (DT_##Signature##->GetRowMap().Find(RowName) != nullptr)\
{\
auto Result = DT_##Signature##->FindRow<F##Signature##>(RowName, TEXT("None"), true);\
return Result;\
}\
\
return nullptr;\
};






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


	DataTable_Signature(ItemGridType1Attr)
	
	DataTable_Signature(ConsumablesItemAttr)
	DataTable_Signature(WeaponItemAttr)
	DataTable_Signature(WearableEquipmentItemAttr)
	DataTable_Signature(ImportantItemAttr)
	DataTable_Signature(MagicItemAttr)
	DataTable_Signature(RingItemAttr)
};
