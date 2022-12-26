// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuTopType1.h"

#include "PaperSpriteBlueprintLibrary.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "DS3_Inventory/Utils/DataAssetMananger/DataAssetMananger.h"
#include "Paper2D/Classes/PaperSprite.h"

void UMenuTopType1::Init(FMenuTopType1Attr MenuTopType1Attr)
{
	// init MenuTop
	MenuTopSizeBox->WidthOverride = MenuTopType1Attr.WidgetSize.X;
	MenuTopSizeBox->HeightOverride = MenuTopType1Attr.WidgetSize.Y;

	MenuTopBGBorder->SetVisibility(ESlateVisibility::Collapsed);
	
	MenuSelectImage->SetVisibility(ESlateVisibility::Collapsed);
	ItemSelectImage->SetVisibility(ESlateVisibility::Collapsed);

	MenuSelectText->SetVisibility(ESlateVisibility::Collapsed);
	ItemSelectText->SetVisibility(ESlateVisibility::Collapsed);

	ADataAssetMananger::RequestAsyncLoadObjects(this, { FName("MenuTopBGImgStyle1"), FName("MenuSelectImgStyle1"), FName("ItemSelectImgStyle1") },
		[this](TArray<UObject*> AssetObjs)
		{
			auto BGImgSprite = Cast<UPaperSprite>(AssetObjs[0]);
			auto MenuSelectImgSprite = Cast<UPaperSprite>(AssetObjs[1]);
			auto ItemSelectImgSprite = Cast<UPaperSprite>(AssetObjs[2]);

			// copied from UPaperSpriteBlueprintLibrary::MakeBrushFromSprite(...)
			{
				const FSlateAtlasData SpriteAtlasData = BGImgSprite->GetSlateAtlasData();
				const FVector2D SpriteSize = SpriteAtlasData.GetSourceDimensions();
				FSlateBrush Brush;
				Brush.SetResourceObject(BGImgSprite);
				Brush.ImageSize = SpriteSize;
				MenuTopBGBorder->SetBrush(Brush);
			}
			
			{
				const FSlateAtlasData SpriteAtlasData = MenuSelectImgSprite->GetSlateAtlasData();
				const FVector2D SpriteSize = SpriteAtlasData.GetSourceDimensions();
				FSlateBrush Brush;
				Brush.SetResourceObject(MenuSelectImgSprite);
				Brush.ImageSize = SpriteSize;
				MenuSelectImage->SetBrush(Brush);
			}
			
			{
				const FSlateAtlasData SpriteAtlasData = ItemSelectImgSprite->GetSlateAtlasData();
				const FVector2D SpriteSize = SpriteAtlasData.GetSourceDimensions();
				FSlateBrush Brush;
				Brush.SetResourceObject(ItemSelectImgSprite);
				Brush.ImageSize = SpriteSize;
				ItemSelectImage->SetBrush(Brush);
			}
			MenuTopBGBorder->SetVisibility(ESlateVisibility::Visible);
		}
	);
	
	// TODO : init MenuButtons and QuickBar
}
