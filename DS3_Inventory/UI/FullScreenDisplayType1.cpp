// Fill out your copyright notice in the Description page of Project Settings.


#include "FullScreenDisplayType1.h"

#include "PaperSprite.h"
#include "Components/Image.h"
#include "Components/NamedSlot.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "DS3_Inventory/Utils/DataAssetMananger/DataAssetMananger.h"

void UFullScreenDisplayType1::NativeConstruct()
{
	Super::NativeConstruct();
	this->SetVisibility(ESlateVisibility::Collapsed);
}

void UFullScreenDisplayType1::Init(FFullScreenDisplayType1Attr FullScreenDisplayType1Attr, TArray<FName> WidgetPartsClassName)
{
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

	// temp init for inventory widget
	for (auto WidgetPartClassName : WidgetPartsClassName)
	{
		auto *WidgetPartClass = ADataAssetMananger::RequestSyncLoadClass(this, WidgetPartClassName);
		auto *Widget = CreateWidget<UUserWidget>(GetOwningPlayer(), WidgetPartClass);
		Widgets.Add(Widget);
	}
	
	SlotLeft->AddChild(Widgets[0]);
	SlotMiddle->AddChild(Widgets[1]);
	SlotRight->AddChild(Widgets[2]);
	

	// TODO : init the 3 widget part individually
	
	// // helper string to get SkinType
	// const FString SkinTypeConfigSectionPrefix = FString("GameUIInit/ItemParts/");
	// const FString SkinTypeKeyPostfix = FString("SkinType");
	//
	// // init 3 widget individually
	// for (auto WidgetPartClassName : WidgetPartsClassName)
	// {
	// 	// get SkinType
	// 	FString OutSkinType;
	// 	
	// 	FString ConfigSection = SkinTypeConfigSectionPrefix + WidgetPartClassName.ToString();
	// 	FString SkinTypeKey = WidgetPartClassName.ToString() + SkinTypeKeyPostfix;		
	// 	GConfig->GetString(
	// 		*ConfigSection,
	// 		*SkinTypeKey,
	// 		OutSkinType,
	// 		GGameIni
	// 	);
	//
	// 	// load widget class
	// 	ADataAssetMananger::RequestAsyncLoadClass(this, WidgetPartClassName, [this](UClass *ClassAsset)
	// 	{
	// 		auto *Widget = CreateWidget<UUIState>(this->GetOwningPlayer(), ClassAsset);
	// 		
	// 		auto *FuncPtr= Widget->FindFunction(FName("Init"));
	// 		if (FuncPtr)
	// 		{
	// 			Widget->ProcessEvent(FuncPtr, nullptr);
	// 		}
	// 	});
	// }
}
