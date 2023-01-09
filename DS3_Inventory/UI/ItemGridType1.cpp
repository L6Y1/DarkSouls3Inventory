// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemGridType1.h"

#include "PaperSprite.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"

#include "DS3_Inventory/Utils/ListViewData.h"
#include "DS3_Inventory/Utils/DataAssetMananger/DataAssetMananger.h"
#include "DS3_Inventory/Utils/DataTableTool/DataTableTool.h"
#include "DS3_Inventory/Utils/FileTool/FileTool.h"


void UItemGridType1::NativeConstruct()
{
	Super::NativeConstruct();
}

void UItemGridType1::NativeDestruct()
{
	Super::NativeDestruct();
}

void UItemGridType1::NativeOnListItemObjectSet(UObject *ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	
	auto ListViewData = Cast<UListViewData>(ListItemObject);

	// the index of currently displaying ListViewData
	CurrentItemIndex = ListViewData->Index;
	
	ItemGridSizeBox->SetWidthOverride(ListViewData->ItemGridAttr.GridSize.X);
	ItemGridSizeBox->SetHeightOverride(ListViewData->ItemGridAttr.GridSize.Y);

	DishImageSizeBox->SetWidthOverride(ListViewData->ItemGridAttr.DishImageSize.X);
	DishImageSizeBox->SetHeightOverride(ListViewData->ItemGridAttr.DishImageSize.Y);

	ItemImageSizeBox->SetWidthOverride(ListViewData->ItemGridAttr.ItemImageSize.X);
	ItemImageSizeBox->SetHeightOverride(ListViewData->ItemGridAttr.ItemImageSize.Y);
	
	
	auto GridData = FGameSaveTool::GetClassifiedGridDataByIndex(ListViewData->ItemClassification, CurrentItemIndex);

	if (GridData.ItemID == 0)
	{
		ADataAssetMananger::RequestAsyncLoadObjects(this,
		{
			ListViewData->ItemGridAttr.GridBaseImage,
			ListViewData->ItemGridAttr.DishImage,
					},
		[this, ListViewData](TArray<UObject*> AssetObjs)
		{
			auto GridBaseImageSprite = Cast<UPaperSprite>(AssetObjs[0]);
			auto DishImageTexture = Cast<UTexture2D>(AssetObjs[1]);
			
			{
				const FSlateAtlasData SpriteAtlasData = GridBaseImageSprite->GetSlateAtlasData();
				const FVector2D SpriteSize = SpriteAtlasData.GetSourceDimensions();
				FSlateBrush Brush;
				Brush.SetResourceObject(GridBaseImageSprite);
				Brush.ImageSize = SpriteSize;
				ItemGridBaseImage->SetBrush(Brush);
			}

			DishImage->SetBrushFromTexture(DishImageTexture);
		});
		ItemImage->SetVisibility(ESlateVisibility::Collapsed);
		ItemNumText->SetVisibility(ESlateVisibility::Collapsed);
		SelectImage->SetVisibility(ESlateVisibility::Collapsed);
		DishImage->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}
	
	// get item attributes by GridData.ID in corresponding DataTable
	FInventoryItemAttr *Attr = nullptr;
	switch (ListViewData->ItemClassification)
	{
	default:
		checkf(Attr != nullptr, TEXT("Attr is nullpointer"));
		break;
	case 0:
		Attr = FDataTableTool::GetConsumablesItemAttr(IntToName(GridData.ItemID));
		break;
	case 1:
		Attr = FDataTableTool::GetWeaponItemAttr(IntToName(GridData.ItemID));
		break;
	case 2:
		Attr = FDataTableTool::GetWearableEquipmentItemAttr(IntToName(GridData.ItemID));
		break;
	case 3:
		Attr = FDataTableTool::GetImportantItemAttr(IntToName(GridData.ItemID));
		break;
	case 4:
		Attr = FDataTableTool::GetMagicItemAttr(IntToName(GridData.ItemID));
		break;
	case 5:
		Attr = FDataTableTool::GetRingItemAttr(IntToName(GridData.ItemID));
		break;
	}

	ItemNumText->SetText(FText::FromString(FString::FromInt(GridData.Num)));
	Attr->bShowNum ? ItemNumText->SetVisibility(ESlateVisibility::Visible) : ItemNumText->SetVisibility(ESlateVisibility::Collapsed);
	
	
	ADataAssetMananger::RequestAsyncLoadObjects(this,
		{
			ListViewData->ItemGridAttr.GridBaseImage,
			ListViewData->ItemGridAttr.DishImage,
			ListViewData->ItemGridAttr.SelectImage,
			Attr->ItemImage
					},
		[this, ListViewData](TArray<UObject*> AssetObjs)
		{
			auto GridBaseImageSprite = Cast<UPaperSprite>(AssetObjs[0]);
			auto DishImageTexture = Cast<UTexture2D>(AssetObjs[1]);
			auto SelectImageSprite = Cast<UPaperSprite>(AssetObjs[2]);
			auto ItemImageTexture = Cast<UTexture2D>(AssetObjs[3]);
			
			{
				const FSlateAtlasData SpriteAtlasData = GridBaseImageSprite->GetSlateAtlasData();
				const FVector2D SpriteSize = SpriteAtlasData.GetSourceDimensions();
				FSlateBrush Brush;
				Brush.SetResourceObject(GridBaseImageSprite);
				Brush.ImageSize = SpriteSize;
				ItemGridBaseImage->SetBrush(Brush);
			}

			DishImage->SetBrushFromTexture(DishImageTexture);
			
			{
				const FSlateAtlasData SpriteAtlasData = SelectImageSprite->GetSlateAtlasData();
				const FVector2D SpriteSize = SpriteAtlasData.GetSourceDimensions();
				FSlateBrush Brush;
				Brush.SetResourceObject(SelectImageSprite);
				Brush.ImageSize = SpriteSize;
				SelectImage->SetBrush(Brush);
				SelectImage->SetVisibility(ESlateVisibility::Collapsed);
			}
			
			ItemImage->SetBrushFromTexture(ItemImageTexture);
			
		});
	
}
