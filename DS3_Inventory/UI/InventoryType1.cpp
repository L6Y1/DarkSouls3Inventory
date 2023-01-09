// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryType1.h"
#include "PaperSprite.h"
#include "Components/Image.h"
#include "Components/NamedSlot.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/TileView.h"
#include "DS3_Inventory/Utils/ListViewData.h"
#include "DS3_Inventory/Utils/DataAssetMananger/DataAssetMananger.h"
#include "DS3_Inventory/Utils/DataTableTool/DataTableTool.h"
#include "DS3_Inventory/Utils/FileTool/FileTool.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Slate/SlateTextureAtlasInterface.h"



void UInventoryType1::NativeConstruct()
{
	Super::NativeConstruct();
	// UKismetSystemLibrary::PrintString(nullptr, "Inventory Construct");

}

void UInventoryType1::NativeDestruct()
{
	Super::NativeDestruct();
}

void UInventoryType1::Init(FInventoryType1Attr InventoryAttr)
{
	ItemNameText->SetVisibility(ESlateVisibility::Collapsed);
	InventoryBaseImage->SetVisibility(ESlateVisibility::Collapsed);
	
	InventorySizeBox->SetWidthOverride(InventoryAttr.InventorySize.X);
	InventorySizeBox->SetHeightOverride(InventoryAttr.InventorySize.Y);
	InventoryBaseSizeBox->SetWidthOverride(InventoryAttr.InventoryBaseImageSize.X);
	InventoryBaseSizeBox->SetHeightOverride(InventoryAttr.InventoryBaseImageSize.Y);

	ADataAssetMananger::RequestAsyncLoadObject(this, InventoryAttr.InventoryBaseImage, [this](UObject* AssetObj)
	{
		auto InventoryBaseImageSprite = Cast<UPaperSprite>(AssetObj);
		{
			const FSlateAtlasData SpriteAtlasData = InventoryBaseImageSprite->GetSlateAtlasData();
			const FVector2D SpriteSize = SpriteAtlasData.GetSourceDimensions();
			FSlateBrush Brush;
			Brush.SetResourceObject(InventoryBaseImageSprite);
			Brush.ImageSize = SpriteSize;
			InventoryBaseImage->SetBrush(Brush);
		}
	});
	InventoryBaseImage->SetVisibility(ESlateVisibility::Visible);

	
	
	FString SortCardsSkinType;
	GConfig->GetString(
		TEXT("GameUIInit/ItemParts/InventoryWidgetType1/SortCardWidgetType1"),
		TEXT("SortCardWidgetType1SkinType"),
		SortCardsSkinType,
		GGameIni
	);

	// init SortCards
	auto *SortCardsAttr = FDataTableTool::GetSortCardsType1Attr(FName(SortCardsSkinType));
	ADataAssetMananger::RequestAsyncLoadClass(this, InventoryAttr.SortCardWidgetClass, [this, SortCardsAttr](UClass *ClassAsset)
	{
		auto *SortCardsWidget = CreateWidget(GetOwningPlayer(), ClassAsset);
		auto *FuncPtr = SortCardsWidget->FindFunction(FName("Init"));
		if (FuncPtr)
		{
			SortCardsWidget->ProcessEvent(FuncPtr, SortCardsAttr);
		}
		SortCardsSlot->AddChild(SortCardsWidget);
	});


	// init grids
	OnClassificationChange(EItemClassification::Consumables);
	
	// UKismetSystemLibrary::PrintString(nullptr, "Inventory INIT()");
}

void UInventoryType1::OnClassificationChange(TEnumAsByte<EItemClassification> NewClassification)
{
	ItemsTileView->ClearListItems();
	FString ItemGridSkinType;
	
	GConfig->GetString(
		TEXT("GameUIInit/ItemParts/InventoryWidgetType1/ItemGridWidgetType1"),
		TEXT("ItemGridWidgetType1SkinType"),
		ItemGridSkinType,
		GGameIni
	);
	auto ItemGridAttr = FDataTableTool::GetItemGridType1Attr(FName(ItemGridSkinType));
	
	for (int i = 0; i < 25; ++i)
	{
		auto GridData = FGameSaveTool::GetClassifiedGridDataByIndex(NewClassification, i);
		UListViewData *Item = NewObject<UListViewData>();
		Item->Index = i;
		Item->ItemClassification = NewClassification;
		Item->ItemGridAttr = *ItemGridAttr;
		ItemsTileView->AddItem(Item);
	}
}

FReply UInventoryType1::NativeOnFocusReceived(const FGeometry &InGeometry, const FFocusEvent &InFocusEvent)
{
	// UKismetSystemLibrary::PrintString(nullptr, "Focus");
	return Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
}

void UInventoryType1::NativeOnFocusLost(const FFocusEvent &InFocusEvent)
{
	// UKismetSystemLibrary::PrintString(nullptr, "FocusLost");
	Super::NativeOnFocusLost(InFocusEvent);
}
