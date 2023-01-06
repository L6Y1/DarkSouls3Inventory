// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTableTool.h"

#include "Engine/DataTable.h"

UDataTable *FDataTableTool::DT_MenuTopType1Attr = nullptr;
UDataTable *FDataTableTool::DT_NavButtonAttr = nullptr;
UDataTable *FDataTableTool::DT_FullScreenDisplayType1Attr = nullptr;
UDataTable *FDataTableTool::DT_InventoryType1Attr = nullptr;
UDataTable *FDataTableTool::DT_SortCardsType1Attr = nullptr;

FMenuTopType1Attr * FDataTableTool::GetMenuTopType1Attr(FName RowName)
{
	if (!DT_MenuTopType1Attr)
	{
		DT_MenuTopType1Attr = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/DataTables/DT_MenuTopType1Attr.DT_MenuTopType1Attr'"));
		check(DT_MenuTopType1Attr);
	}

	if (DT_MenuTopType1Attr->GetRowMap().Contains(RowName))
	{
		auto Result = DT_MenuTopType1Attr->FindRow<FMenuTopType1Attr>(RowName, TEXT("None"), true);
		return Result;
	}
	return nullptr;
}

FNavButtonAttr * FDataTableTool::GetNavButtonAttr(FName RowName)
{
	if (!DT_NavButtonAttr)
	{
		DT_NavButtonAttr = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/DataTables/DT_NavButtonAttr.DT_NavButtonAttr'"));
		check(DT_NavButtonAttr);
	}

	if (DT_NavButtonAttr->GetRowMap().Contains(RowName))
	{
		auto Result = DT_NavButtonAttr->FindRow<FNavButtonAttr>(RowName, TEXT("None"), true);
		return Result;
	}
	return nullptr;
}

FFullScreenDisplayType1Attr * FDataTableTool::GetFullScreenDisplayType1Attr(FName RowName)
{
	if (!DT_FullScreenDisplayType1Attr)
	{
		DT_FullScreenDisplayType1Attr = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/DataTables/DT_FullScreenDisplayType1Attr.DT_FullScreenDisplayType1Attr'"));
		check(DT_FullScreenDisplayType1Attr);
	}

	if (DT_FullScreenDisplayType1Attr->GetRowMap().Contains(RowName))
	{
		auto Result = DT_FullScreenDisplayType1Attr->FindRow<FFullScreenDisplayType1Attr>(RowName, TEXT("None"), true);
		return Result;
	}
	return nullptr;
}

FInventoryType1Attr * FDataTableTool::GetInventoryType1Attr(FName RowName)
{
	if (!DT_InventoryType1Attr)
	{
		DT_InventoryType1Attr = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/DataTables/DT_InventoryType1Attr.DT_InventoryType1Attr'"));
		check(DT_InventoryType1Attr);
	}

	if (DT_InventoryType1Attr->GetRowMap().Contains(RowName))
	{
		auto Result = DT_InventoryType1Attr->FindRow<FInventoryType1Attr>(RowName, TEXT("None"), true);
		return Result;
	}
	return nullptr;
}

FSortCardsType1Attr * FDataTableTool::GetSortCardsType1Attr(FName RowName)
{
	if (!DT_SortCardsType1Attr)
	{
		DT_SortCardsType1Attr = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/DataTables/DT_SortCardsType1Attr.DT_SortCardsType1Attr'"));
		check(DT_SortCardsType1Attr);
	}

	if (DT_SortCardsType1Attr->GetRowMap().Contains(RowName))
	{
		auto Result = DT_SortCardsType1Attr->FindRow<FSortCardsType1Attr>(RowName, TEXT("None"), true);
		return Result;
	}
	return nullptr;
}



DataTable_Impl(ItemGridType1Attr, TEXT("DataTable'/Game/DataTables/DT_ItemGridType1Attr.DT_ItemGridType1Attr'"))
	
DataTable_Impl(ConsumablesItemAttr, TEXT("DataTable'/Game/DataTables/ItemsDT/DT_Consumables.DT_Consumables'"))
DataTable_Impl(WeaponItemAttr, TEXT("DataTable'/Game/DataTables/ItemsDT/DT_Weapon.DT_Weapon'"))
DataTable_Impl(WearableEquipmentItemAttr, TEXT("DataTable'/Game/DataTables/ItemsDT/DT_WearableEquipment.DT_WearableEquipment'"))
DataTable_Impl(ImportantItemAttr, TEXT("DataTable'/Game/DataTables/ItemsDT/DT_Important.DT_Important'"))
DataTable_Impl(MagicItemAttr, TEXT("DataTable'/Game/DataTables/ItemsDT/DT_Magic.DT_Magic'"))
DataTable_Impl(RingItemAttr, TEXT("DataTable'/Game/DataTables/ItemsDT/DT_Ring.DT_Ring'"))


