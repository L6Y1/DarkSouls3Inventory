// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusType1.h"

#include "PaperSprite.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Image.h"
#include "Components/Spacer.h"
#include "Components/VerticalBox.h"
#include "DS3_Inventory/Utils/DataAssetMananger/DataAssetMananger.h"
#include "DS3_Inventory/Utils/FileTool/FileTool.h"
#include "Kismet/KismetSystemLibrary.h"

void UStatusType1::Init(FStatusType1Attr StatusAttr)
{
	ADataAssetMananger::RequestAsyncLoadObject(this, StatusAttr.StatusBaseImage, [this](UObject *AssetObj)
	{
		auto BaseImageSprite = Cast<UPaperSprite>(AssetObj);
		{
			const FSlateAtlasData SpriteAtlasData = BaseImageSprite->GetSlateAtlasData();
			const FVector2D SpriteSize = SpriteAtlasData.GetSourceDimensions();
			FSlateBrush Brush;
			Brush.SetResourceObject(BaseImageSprite);
			Brush.ImageSize = SpriteSize;
			StatusBaseImage->SetBrush(Brush);
		}
	});
	
	
	auto PlayerStats = FGameSaveTool::GetGameSaveData().PlayerData.PlayerStats;
	TMap<FString, int> AllStats;
	
	for (TFieldIterator<FProperty> It(PlayerStats.StaticStruct()); It; ++It)
	{
		auto *Property = *It;
		if (Property->IsA<FIntProperty>())
		{
			FString VariableName = Property->GetName();
			AllStats.Add(VariableName, *Property->ContainerPtrToValuePtr<int>(&PlayerStats));
		}else if (Property->IsA<FMapProperty>())
		{
			auto MapPtr = Property->ContainerPtrToValuePtr<TMap<TEnumAsByte<EPlayerStats>, int>>(&PlayerStats);
			for (auto KeyValuePair : *MapPtr)
			{
				AllStats.Add(UEnum::GetValueAsName(KeyValuePair.Key).ToString(), KeyValuePair.Value);
			}
		}
		
	}
	AllStats.Remove("CurrentHP");
	AllStats.Remove("CurrentFP");
	
	auto *UnitClass = ADataAssetMananger::RequestSyncLoadClass(this, StatusAttr.StatusUnitClass);
	
	int temp = 0;
    for (auto Stat : AllStats)
    {
    	Stat.Key = StatusAttr.StatsImages.Find(Stat.Key)->ToString();
    	CreateAndBindStatusUnit(Stat, UnitClass);
    	
    	if (temp == 1)
    	{
    		auto Spacer = WidgetTree->ConstructWidget<USpacer>();
    		Spacer->SetSize(FVector2D(1, 20));
    		StatsVerticalBox->AddChildToVerticalBox(Spacer);
    	}else if (temp == 10)
    	{
    		auto Spacer = WidgetTree->ConstructWidget<USpacer>();
    		Spacer->SetSize(FVector2D(1, 20));
    		StatsVerticalBox->AddChildToVerticalBox(Spacer);
    	}else if (temp == 14)
    	{
    		auto Spacer = WidgetTree->ConstructWidget<USpacer>();
    		Spacer->SetSize(FVector2D(1, 45));
    		StatsVerticalBox->AddChildToVerticalBox(Spacer);
    	}
    	
    	++temp;
    }
	
}

void UStatusType1::CreateAndBindStatusUnit(TTuple<FString, int> Data, UClass *UnitClass)
{
	auto UnitWidget = CreateWidget(GetOwningPlayer(), UnitClass);
	auto *FuncPtr = UnitWidget->FindFunction(FName("Init"));
	if (FuncPtr)
	{
		struct 
		{
			FString Name;
			int Value;
		} Params;
		Params.Name = Data.Key;
		Params.Value = Data.Value;
		
		UnitWidget->ProcessEvent(FuncPtr, &Params);
	}
	StatsVerticalBox->AddChildToVerticalBox(UnitWidget);
	
	if (DividerStyle4Class == nullptr)
	{
		DividerStyle4Class = ADataAssetMananger::RequestSyncLoadClass(this, FName("DividerStyle4"));
	}
	auto Divider = CreateWidget<UUserWidget>(GetOwningPlayer(), DividerStyle4Class);
	StatsVerticalBox->AddChildToVerticalBox(Divider);
}
