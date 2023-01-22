// Fill out your copyright notice in the Description page of Project Settings.


#include "FullScreenDisplayType1.h"

#include "PaperSprite.h"
#include "Components/Image.h"
#include "Components/NamedSlot.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "DS3_Inventory/Utils/DataAssetMananger/DataAssetMananger.h"
#include "DS3_Inventory/Utils/DataTableTool/DataTableTool.h"
#include "DS3_Inventory/Utils/GlobalEventManager/GlobalEventManager.h"
#include "Kismet/KismetSystemLibrary.h"


#define DataTableSearch(WidgetName, Param)\
auto *Attr = FDataTableTool::Get##WidgetName##(Param);



void UFullScreenDisplayType1::NativeConstruct()
{
	Super::NativeConstruct();
	// UKismetSystemLibrary::PrintString(nullptr, "FullScreen Construct");
	FGlobalEventManager::RegisterEvent(FName("ItemSelectedEvent"), this, FName("CreateDescription"));

}

void UFullScreenDisplayType1::Init(FFullScreenDisplayType1Attr FullScreenDisplayType1Attr, TArray<FName> WidgetPartsClassName)
{
	this->SetVisibility(ESlateVisibility::Collapsed);
	TitleImageSizeBox->SetWidthOverride(FullScreenDisplayType1Attr.TitleImageSize.X);
	TitleImageSizeBox->SetHeightOverride(FullScreenDisplayType1Attr.TitleImageSize.Y);

	TitleText->SetText(FText::FromName(FullScreenDisplayType1Attr.TitleText));

	// init images(Title, TitleBG, TooterBG, MenuBase) 
	ADataAssetMananger::RequestAsyncLoadObjects(this,
		{ FullScreenDisplayType1Attr.TitleBGImage, FullScreenDisplayType1Attr.TitleImage, FullScreenDisplayType1Attr.FooterBGImage, FullScreenDisplayType1Attr.MenuBaseImage },
		[this](TArray<UObject*> AssetObjs)
		{
			auto TitleBGImageSprite = Cast<UPaperSprite>(AssetObjs[0]);
			auto TitleImageSprite = Cast<UPaperSprite>(AssetObjs[1]);
			auto FooterBGImageSprite = Cast<UPaperSprite>(AssetObjs[2]);
			auto MenuBaseImageSprite = Cast<UPaperSprite>(AssetObjs[3]);
			
			{
				const FSlateAtlasData SpriteAtlasData = TitleBGImageSprite->GetSlateAtlasData();
				const FVector2D SpriteSize = SpriteAtlasData.GetSourceDimensions();
				FSlateBrush Brush;
				Brush.SetResourceObject(TitleBGImageSprite);
				Brush.ImageSize = SpriteSize;
				TitleBGImage->SetBrush(Brush);
			}

			{
				const FSlateAtlasData SpriteAtlasData = TitleImageSprite->GetSlateAtlasData();
				const FVector2D SpriteSize = SpriteAtlasData.GetSourceDimensions();
				FSlateBrush Brush;
				Brush.SetResourceObject(TitleImageSprite);
				Brush.ImageSize = SpriteSize;
				TitleImage->SetBrush(Brush);
			}

			{
				const FSlateAtlasData SpriteAtlasData = FooterBGImageSprite->GetSlateAtlasData();
				const FVector2D SpriteSize = SpriteAtlasData.GetSourceDimensions();
				FSlateBrush Brush;
				Brush.SetResourceObject(FooterBGImageSprite);
				Brush.ImageSize = SpriteSize;
				FooterBGImage->SetBrush(Brush);
			}

			{
				const FSlateAtlasData SpriteAtlasData = MenuBaseImageSprite->GetSlateAtlasData();
				const FVector2D SpriteSize = SpriteAtlasData.GetSourceDimensions();
				FSlateBrush Brush;
				Brush.SetResourceObject(MenuBaseImageSprite);
				Brush.ImageSize = SpriteSize;
				MenuBaseImage->SetBrush(Brush);
			}
			
			this->SetVisibility(ESlateVisibility::Visible);
		}
	);
	
	TArray<UUserWidget*> Widgets;
	TArray<FString> SkinTypes;
	
	// helper string to get SkinType
	const FString SkinTypeConfigSectionPrefix = FString("GameUIInit/ItemParts/");
	const FString SkinTypeKeyPostfix = FString("SkinType");
	
	for (auto WidgetPartClassName : WidgetPartsClassName)
	{
		// get SkinType
		FString OutSkinType;
		
		FString ConfigSection = SkinTypeConfigSectionPrefix + WidgetPartClassName.ToString();
		FString SkinTypeKey = WidgetPartClassName.ToString() + SkinTypeKeyPostfix;		
		GConfig->GetString(
			*ConfigSection,
			*SkinTypeKey,
			OutSkinType,
			GGameIni
		);
		SkinTypes.Add(OutSkinType);
		
		auto *WidgetPartClass = ADataAssetMananger::RequestSyncLoadClass(this, WidgetPartClassName);
		auto *Widget = CreateWidget<UUserWidget>(GetOwningPlayer(), WidgetPartClass);
		Widgets.Add(Widget);
	}

	auto *InventoryAttr = FDataTableTool::GetInventoryType1Attr(FName(SkinTypes[0]));
	
	{
		auto *FuncPtr = Widgets[0]->FindFunction(FName("Init"));
		if (FuncPtr)
		{
			Widgets[0]->ProcessEvent(FuncPtr, InventoryAttr);
		}
	}

	auto *StatusAttr = FDataTableTool::GetStatusType1Attr(FName(SkinTypes[2]));
	{
		auto *FuncPtr = Widgets[2]->FindFunction(FName("Init"));
		if (FuncPtr)
		{
			Widgets[2]->ProcessEvent(FuncPtr, StatusAttr);
		}
	}

	

	
	// add 3 widgets to corresponding slot
	SlotLeft->AddChild(Widgets[0]);
	SlotMiddle->AddChild(Widgets[1]);
	SlotRight->AddChild(Widgets[2]);

	// UKismetSystemLibrary::PrintString(nullptr, "FullScreen INIT()");
}

void UFullScreenDisplayType1::CreateDescription(FName ItemName, int ItemID)
{
	if (ItemID == 0) return;

	SlotMiddle->ClearChildren();

	auto *Attr = FDataTableTool::GetInventoryItemAttrByID(ItemID);
	
	auto DesClass = ADataAssetMananger::RequestSyncLoadClass(this, FName("Description"));
	auto DesWidget = CreateWidget(GetOwningPlayer(), DesClass);

	auto *FuncPtr = DesWidget->FindFunction(FName("Init"));
	if (FuncPtr)
	{
		struct
		{
			FName ItemImageName;
			FName ItemName;
			int ItemID;
		} Params;
		Params.ItemImageName = Attr->ItemImage;
		Params.ItemName = ItemName;
		Params.ItemID = ItemID;
		DesWidget->ProcessEvent(FuncPtr, &Params);
	}
	SlotMiddle->AddChild(DesWidget);
}