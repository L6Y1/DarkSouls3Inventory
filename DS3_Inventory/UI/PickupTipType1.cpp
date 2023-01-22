// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupTipType1.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "DS3_Inventory/Utils/DataAssetMananger/DataAssetMananger.h"
#include "DS3_Inventory/Utils/GlobalEventManager/GlobalEventManager.h"

void UPickupTipType1::NativeConstruct()
{
	Super::NativeConstruct();
	bIsFocusable = true;
	SetFocus();
}

FReply UPickupTipType1::NativeOnKeyDown(const FGeometry &InGeometry, const FKeyEvent &InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);
	if (InKeyEvent.GetKey() == EKeys::E)
	{
		bIsFocusable = false;
		this->RemoveFromParent();
		this->Destruct();
	}
	return FReply::Handled();
}


void UPickupTipType1::Init(FName ItemName, FName ItemImageName, int Num)
{
	ADataAssetMananger::RequestAsyncLoadObject(this, ItemImageName, [this](UObject *AssetObj)
	{
		auto ItemImageTexture = Cast<UTexture2D>(AssetObj);
		ItemImage->SetBrushFromTexture(ItemImageTexture);
	});
	ItemNameText->SetText(FText::FromName(ItemName));
	ItemNumText->SetText(FText::FromString(FString::FromInt(Num)));
	
}
