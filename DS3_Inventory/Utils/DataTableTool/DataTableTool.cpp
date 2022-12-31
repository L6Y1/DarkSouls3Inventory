// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTableTool.h"

#include "Engine/DataTable.h"

UDataTable *FDataTableTool::DT_MenuTopType1Attr = nullptr;
UDataTable *FDataTableTool::DT_NavButtonAttr = nullptr;
UDataTable *FDataTableTool::DT_FullScreenDisplayType1Attr = nullptr;

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
