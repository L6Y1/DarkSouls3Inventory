// Fill out your copyright notice in the Description page of Project Settings.


#include "SortCard.h"

#include "PaperSprite.h"
#include "Components/Image.h"
#include "Components/OverlaySlot.h"
#include "DS3_Inventory/Utils/DataAssetMananger/DataAssetMananger.h"
#include "DS3_Inventory/Utils/GlobalEventManager/GlobalEventManager.h"
#include "Kismet/KismetSystemLibrary.h"

void USortCard::NativeConstruct()
{

	Super::NativeConstruct();
	
	BGImage->SetBrushSize(FVector2D(86, 96));
	SortImage->SetBrushSize(FVector2D(70, 90));
	ShadderImage->SetBrushSize(FVector2D(88, 36));

	BGImageSlot = Cast<UOverlaySlot>(BGImage->Slot);
	SortImageSlot = Cast<UOverlaySlot>(SortImage->Slot);
	ShadderImageSlot = Cast<UOverlaySlot>(ShadderImage->Slot);

	BGImageSlot->SetHorizontalAlignment(HAlign_Center);
	BGImageSlot->SetVerticalAlignment(VAlign_Bottom);

	SortImageSlot->SetHorizontalAlignment(HAlign_Center);
	SortImageSlot->SetVerticalAlignment(VAlign_Bottom);

	ShadderImageSlot->SetHorizontalAlignment(HAlign_Fill);
	ShadderImageSlot->SetVerticalAlignment(VAlign_Center);

	FGlobalEventManager::RegisterEvent(FName("CardActiveEvent"), this, FName("OnCardActive"));

}

void USortCard::NativeDestruct()
{
	Super::NativeDestruct();
	FGlobalEventManager::UnRegisterEvent(FName("CardActiveEvent"), this);
	
}

void USortCard::NativeOnMouseEnter(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	FGlobalEventManager::TriggerEvent(FName("CardActiveEvent"), &CardIndex);
	
}



void USortCard::Init(TEnumAsByte<ItemClassification> Index, FName ImageName)
{
	this->CardIndex = Index;
	ADataAssetMananger::RequestAsyncLoadObject(this, ImageName, [this](UObject *AssetObj)
	{
		auto CardImageSprite = Cast<UPaperSprite>(AssetObj);
		{
			const FSlateAtlasData SpriteAtlasData = CardImageSprite->GetSlateAtlasData();
			const FVector2D SpriteSize = SpriteAtlasData.GetSourceDimensions();
			FSlateBrush Brush;
			Brush.SetResourceObject(CardImageSprite);
			Brush.ImageSize = SpriteSize;
			SortImage->SetBrush(Brush);
		}
	});

}

void USortCard::PopUp()
{
	// the SortCard pop up Effect 
	ShadderImage->SetVisibility(ESlateVisibility::Hidden);
	BGImageSlot->SetVerticalAlignment(VAlign_Top);
	SortImageSlot->SetVerticalAlignment(VAlign_Top);
}

void USortCard::PopDown()
{
	// the SortCard reset Effect
	ShadderImage->SetVisibility(ESlateVisibility::Visible);
	BGImageSlot->SetVerticalAlignment(VAlign_Bottom);
	SortImageSlot->SetVerticalAlignment(VAlign_Bottom);
}

void USortCard::OnCardActive(TEnumAsByte<ItemClassification> Index)
{
	if (CardIndex == Index)
	{
		PopUp();
	}
	else
	{
		PopDown();
	}
}