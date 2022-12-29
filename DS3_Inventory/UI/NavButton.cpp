// Fill out your copyright notice in the Description page of Project Settings.


#include "NavButton.h"
#include "PaperSprite.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "DS3_Inventory/Utils/DataAssetMananger/DataAssetMananger.h"
#include "DS3_Inventory/Utils/GlobalEventManager/GlobalEventManager.h"

void UNavButton::NativeConstruct()
{
	Super::NativeConstruct();
	NavButton->SetVisibility(ESlateVisibility::Collapsed);
	HoveredImage->SetVisibility(ESlateVisibility::Collapsed);

	NavButton->OnHovered.AddDynamic(this, &UNavButton::ToggleHoveredPic);
	NavButton->OnHovered.AddDynamic(this, &UNavButton::ShowMenuTopHint);
	NavButton->OnUnhovered.AddDynamic(this, &UNavButton::ToggleHoveredPic);
	NavButton->OnUnhovered.AddDynamic(this, &UNavButton::HideMenuTopHint);
}

void UNavButton::ToggleHoveredPic()
{
	HoveredImage->IsVisible() ?
		HoveredImage->SetVisibility(ESlateVisibility::Collapsed) :
		HoveredImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UNavButton::ShowMenuTopHint()
{
	struct 
	{
		FName Name;
		bool bShouldShow;
		bool bIsMenu;
	} Param;
	Param.Name = Name;
	Param.bShouldShow = true;
	Param.bIsMenu = true;
	FGlobalEventManager::TriggerEvent(FName("UpdateHintEvent"), &Param);
}

void UNavButton::HideMenuTopHint()
{
	struct 
	{
		FName Name;
		bool bShouldShow;
		bool bIsMenu;
	} Param;
	Param.Name = Name;
	Param.bShouldShow = false;
	Param.bIsMenu = true;
	FGlobalEventManager::TriggerEvent(FName("UpdateHintEvent"), &Param);
}

void UNavButton::Init(FName ButtonName, FNavButtonAttr NavButtonAttr)
{
	Name = ButtonName;
	
	NavButtonSizeBox->SetWidthOverride(NavButtonAttr.ButtonSize.X);
	NavButtonSizeBox->SetHeightOverride(NavButtonAttr.ButtonSize.Y);
	
	// TODO : init the NavButton here
	ADataAssetMananger::RequestAsyncLoadObjects(this, { NavButtonAttr.ButtonImage, NavButtonAttr.HoveredImage }, [this](TArray<UObject*> Objs)
	{
		auto ButtonImageSprite = Cast<UPaperSprite>(Objs[0]);
		auto HoveredImageSprite = Cast<UPaperSprite>(Objs[1]);

		auto *ButtonStyle = &NavButton->WidgetStyle;
		
		{
			const FSlateAtlasData SpriteAtlasData = ButtonImageSprite->GetSlateAtlasData();
			const FVector2D SpriteSize = SpriteAtlasData.GetSourceDimensions();
			FSlateBrush Brush;
			Brush.SetResourceObject(ButtonImageSprite);
			Brush.ImageSize = SpriteSize;
			ButtonStyle->SetNormal(Brush);
			ButtonStyle->SetHovered(Brush);
			ButtonStyle->SetPressed(Brush);
			NavButton->SetVisibility(ESlateVisibility::Visible);
		}
		
		{
			const FSlateAtlasData SpriteAtlasData = HoveredImageSprite->GetSlateAtlasData();
			const FVector2D SpriteSize = SpriteAtlasData.GetSourceDimensions();
			FSlateBrush Brush;
			Brush.SetResourceObject(HoveredImageSprite);
			Brush.ImageSize = SpriteSize;
			HoveredImage->SetBrush(Brush);
		}
	});
}


