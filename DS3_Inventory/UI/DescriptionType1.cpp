// Fill out your copyright notice in the Description page of Project Settings.


#include "DescriptionType1.h"
#include "Components/Image.h"
#include "Components/RichTextBlock.h"
#include "Components/TextBlock.h"
#include "DS3_Inventory/Utils/DataAssetMananger/DataAssetMananger.h"
#include "DS3_Inventory/Utils/DataTableTool/DataTableTool.h"

void UDescriptionType1::NativeConstruct()
{
	Super::NativeConstruct();

}

void UDescriptionType1::Init(FName ItemImageName, FName ItemName, int ItemID)
{	
	auto attr = FDataTableTool::GetItemDescription(IntToName(ItemID));
	DescriptionText0->SetText(FText::FromName(attr->Description1));
	DescriptionText1->SetText(FText::FromName(attr->Description2));
	DescriptionText2->SetText(FText::FromName(attr->Description3));

	ItemNameText->SetText(FText::FromName(ItemName));

	ADataAssetMananger::RequestAsyncLoadObject(this, ItemImageName, [this](UObject *AssetObj)
	{
		auto ItemImageTexture = Cast<UTexture2D>(AssetObj);
		
		ItemImage->SetBrushFromTexture(ItemImageTexture);
	});
}
