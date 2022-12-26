// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTableTool.h"

#include "Engine/DataTable.h"

UDataTable *FDataTableTool::DT_MenuTopType1Attr = nullptr;

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
