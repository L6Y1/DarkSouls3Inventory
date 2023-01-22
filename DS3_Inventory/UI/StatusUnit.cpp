// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusUnit.h"

#include "PaperSprite.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "DS3_Inventory/Utils/DataAssetMananger/DataAssetMananger.h"
#include "DS3_Inventory/Utils/DataTableTool/DataTableTool.h"

void UStatusUnit::Init(FString Name, int Value)
{
	ADataAssetMananger::RequestAsyncLoadObject(this, FName(Name), [this](UObject *AssetObj)
	{
		auto ImageSprite = Cast<UPaperSprite>(AssetObj);
		{
			const FSlateAtlasData SpriteAtlasData = ImageSprite->GetSlateAtlasData();
			const FVector2D SpriteSize = SpriteAtlasData.GetSourceDimensions();
			FSlateBrush Brush;
			Brush.SetResourceObject(ImageSprite);
			Brush.ImageSize = SpriteSize;
			StatusImage->SetBrush(Brush);
		}
	});
	StatusText->SetText(FText::FromString(Name.Replace(TEXT("Img"), TEXT(""))));
	StatusValueText->SetText(FText::FromString(FString::FromInt(Value)));
}
