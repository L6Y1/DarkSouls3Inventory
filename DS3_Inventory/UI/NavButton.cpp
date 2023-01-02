// Fill out your copyright notice in the Description page of Project Settings.


#include "NavButton.h"
#include "PaperSprite.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "DS3_Inventory/GameMode/DS3_InventoryPC.h"
#include "DS3_Inventory/Utils/DataAssetMananger/DataAssetMananger.h"
#include "DS3_Inventory/Utils/DataTableTool/DataTableTool.h"
#include "DS3_Inventory/Utils/GlobalEventManager/GlobalEventManager.h"
#include "DS3_Inventory/Utils/UIManager/UIManagerComponent.h"
#include "DS3_Inventory/Utils/UIManager/UIState.h"

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

void UNavButton::NativeOnClick()
{
	FString FullScreenDisplaySkinType;
	GConfig->GetString(
		TEXT("GameUIInit/FullScreenDisplayWidgetType1"),
		TEXT("FullScreenDisplayWidgetType1SkinType"),
		FullScreenDisplaySkinType,
		GGameIni
	);
	
	auto FullScreenDisplayType1Attr = FDataTableTool::GetFullScreenDisplayType1Attr(FName(FullScreenDisplaySkinType));
	
	ADataAssetMananger::RequestAsyncLoadClass(this, SelfAttr.ToggledFullScreenWidgetClass, [this, FullScreenDisplayType1Attr](UClass *ClassAsset)
	{
		auto ToggledWidget = CreateWidget<UUIState>(this->GetOwningPlayer(), ClassAsset);
		
		
		auto *FuncPtr = ToggledWidget->FindFunction(FName("Init"));
		if (FuncPtr)
		{
			struct 
			{
				FFullScreenDisplayType1Attr FullScreenDisplayType1Attr;
				TArray<FName> WidgetPartsClass;
			} Params;
			Params.FullScreenDisplayType1Attr = *FullScreenDisplayType1Attr;
			Params.FullScreenDisplayType1Attr.TitleImage = SelfAttr.ButtonImage;
			Params.FullScreenDisplayType1Attr.TitleText = FName(Name.ToString().Replace(TEXT("Button"), TEXT("")));
			
			Params.WidgetPartsClass = SelfAttr.ToggledFullScreenWidgetPartsClass;
			
			ToggledWidget->ProcessEvent(FuncPtr, &Params);
		}
		
		Cast<ADS3_InventoryPC>(GetOwningPlayer())->UIManagerComponent->PushState(ToggledWidget);
	});
}

void UNavButton::Init(FName ButtonName, FNavButtonAttr NavButtonAttr)
{
	Name = ButtonName;
	SelfAttr = NavButtonAttr;
	
	NavButtonSizeBox->SetWidthOverride(NavButtonAttr.ButtonSize.X);
	NavButtonSizeBox->SetHeightOverride(NavButtonAttr.ButtonSize.Y);
	
	// init ButtonImage and HoveredImage
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

	// Onclick

	NavButton->OnClicked.AddDynamic(this, &UNavButton::NativeOnClick);
}


