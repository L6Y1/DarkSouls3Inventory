// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuTopType1.h"

#include "PaperSpriteBlueprintLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/Spacer.h"
#include "Components/TextBlock.h"
#include "DS3_Inventory/Utils/DataAssetMananger/DataAssetMananger.h"
#include "DS3_Inventory/Utils/DataTableTool/DataTableTool.h"
#include "DS3_Inventory/Utils/GlobalEventManager/GlobalEventManager.h"
#include "Paper2D/Classes/PaperSprite.h"


void UMenuTopType1::NativeConstruct()
{
	Super::NativeConstruct();
	FGlobalEventManager::RegisterEvent(FName("UpdateHintEvent"), this, FName("UpdateHint"));

}

void UMenuTopType1::NativeDestruct()
{
	Super::NativeDestruct();
	FGlobalEventManager::UnRegisterEvent(FName("UpdateHintEvent"), this);
}

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
	MenuSelectText->Font.Size = 10;
	ItemSelectText->Font.Size = 10;

	ADataAssetMananger::RequestAsyncLoadObjects(this, { MenuTopType1Attr.MenuTopBackGroundImg, MenuTopType1Attr.MenuSelectImage, MenuTopType1Attr.ItemSelectImage },
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
	
	
	TArray<FString> NavButtonStrs;
	GConfig->GetArray(
		TEXT("GameUIInit/MainUI/MenuTop/NavButton"),
		TEXT("NavButtons"),
		NavButtonStrs,
		GGameIni
	);

	for (auto NavButtonStr : NavButtonStrs)
	{
		auto *NavButtonAttr = FDataTableTool::GetNavButtonAttr(FName(NavButtonStr));
		checkf(NavButtonAttr, TEXT("%s ButtonAttr Not Found"), *NavButtonStr);

		ADataAssetMananger::RequestAsyncLoadClass(this, NavButtonAttr->ButtonLayoutStyle, [this, NavButtonAttr, NavButtonStr](UClass *ClassAsset)
		{
			auto NavButtonWidget = CreateWidget(this->GetOwningPlayer(), ClassAsset);
			
			auto FuncPtr = NavButtonWidget->FindFunction(FName("Init"));
			if (FuncPtr)
			{
				struct 
				{
					FName ButtonName;
					FNavButtonAttr NavButtonAttr;
				} Params;
				Params.ButtonName = FName(NavButtonStr);
				Params.NavButtonAttr = *NavButtonAttr;
				
				NavButtonWidget->ProcessEvent(FuncPtr, &Params);
			}

			MenuHorBox->AddChildToHorizontalBox(NavButtonWidget);
			auto *Spacer = WidgetTree->ConstructWidget<USpacer>(USpacer::StaticClass());
			Spacer->SetSize(FVector2D(5, 1));
			MenuHorBox->AddChildToHorizontalBox(Spacer);
		});
		
	}


	// TODO : init QuickBar
	
}

void UMenuTopType1::UpdateHint(FName Name, bool bShouldShow, bool bIsMenu)
{
	if (bIsMenu)
	{
		if (bShouldShow)
		{
			MenuSelectText->SetText(FText::FromName(Name));
			MenuSelectText->SetVisibility(ESlateVisibility::Visible);
			MenuSelectImage->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			MenuSelectText->SetText(FText());
			MenuSelectText->SetVisibility(ESlateVisibility::Collapsed);
			MenuSelectImage->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	else
	{
		if (bShouldShow)
		{
			ItemSelectText->SetText(FText::FromName(Name));
			ItemSelectText->SetVisibility(ESlateVisibility::Visible);
			ItemSelectImage->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			ItemSelectText->SetText(FText());
			ItemSelectText->SetVisibility(ESlateVisibility::Collapsed);
			ItemSelectImage->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}