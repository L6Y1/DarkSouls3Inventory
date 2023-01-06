// Fill out your copyright notice in the Description page of Project Settings.


#include "SortCardsType1.h"

#include "SortCard.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "DS3_Inventory/Utils/DataAssetMananger/DataAssetMananger.h"
#include "DS3_Inventory/Utils/GlobalEventManager/GlobalEventManager.h"
#include "Kismet/KismetSystemLibrary.h"

void USortCardsType1::NativeConstruct()
{
	Super::NativeConstruct();
	UKismetSystemLibrary::PrintString(nullptr, FString::FromInt(TotalNum));
	LeftShadder->SetVisibility(ESlateVisibility::Collapsed);
	RightShadder->SetVisibility(ESlateVisibility::Collapsed);

	FGlobalEventManager::RegisterEvent(FName("CardActiveEvent"), this, FName("UpdateActiveIndex"));
	FGlobalEventManager::TriggerEvent(FName("CardActiveEvent"), &CurrentActiveIndex);

	LeftButton->OnClicked.AddDynamic(this, &USortCardsType1::NativeLeftButtonClicked);
	RightButton->OnClicked.AddDynamic(this, &USortCardsType1::NativeRightButtonClicked);
}

void USortCardsType1::NativeDestruct()
{
	Super::NativeDestruct();
	FGlobalEventManager::UnRegisterEvent(FName("CardActiveEvent"), this);
	
}

void USortCardsType1::NativeTick(const FGeometry &MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	UKismetSystemLibrary::PrintString(nullptr, FString("CurrentActive: ") + FString::FromInt(CurrentActiveIndex), true, false, FLinearColor::Yellow, 0);
}


void USortCardsType1::Init(FSortCardsType1Attr SortCardsAttr)
{
	/*TArray<TEnumAsByte<EItemClassification>> OutArray;
	SortCardsAttr.CardImage.GetKeys(OutArray);
	for (auto Temp : OutArray)
	{
		UKismetSystemLibrary::PrintString(nullptr, UEnum::GetValueAsName(Temp).ToString());		
	}*/
	
	// load images and apply them, leave blank here

	SortCardsSizeBox->SetWidthOverride(SortCardsAttr.SortCardsSize.X);
	SortCardsSizeBox->SetHeightOverride(SortCardsAttr.SortCardsSize.Y);
	
	CardContainerSizeBox->SetWidthOverride(SortCardsAttr.CardContainerSize.X);
	CardContainerSizeBox->SetHeightOverride(SortCardsAttr.CardContainerSize.Y);

	CardNum = SortCardsAttr.SortCardNum;
	CardImages = SortCardsAttr.CardImage;
	
	auto *SortCardClass = ADataAssetMananger::RequestSyncLoadClass(this, SortCardsAttr.SortCardType);
	for (int i = 0; i < CardNum; ++i)
	{
		auto *SortCardWidget = CreateWidget(GetOwningPlayer(), SortCardClass);
		auto *FuncPtr = SortCardWidget->FindFunction(FName("Init"));
		if (FuncPtr)
		{
			struct 
			{
				EItemClassification Index;
				FName CardImage;
			} Params;
			Params.Index = TEnumAsByte<EItemClassification>(i);
			Params.CardImage = SortCardsAttr.CardImage.FindRef(Params.Index);
			
			SortCardWidget->ProcessEvent(FuncPtr, &Params);
		}
		SortCardsHorBox->AddChildToHorizontalBox(SortCardWidget)->SetVerticalAlignment(VAlign_Fill);
		
		DisplayingIndex.Add(TEnumAsByte<EItemClassification>(i));
	}

}

void USortCardsType1::UpdateActiveIndex(TEnumAsByte<EItemClassification> Index)
{
	CurrentActiveIndex = Index;
}

void USortCardsType1::NativeLeftButtonClicked()
{
	CurrentActiveIndex - 1 >= 0																? 
	CurrentActiveIndex = TEnumAsByte<EItemClassification>(CurrentActiveIndex - 1)	:
	CurrentActiveIndex = TEnumAsByte<EItemClassification>(5);
	
	// if the active index + 1, is still a displaying index
	if (DisplayingIndex.Contains(CurrentActiveIndex))
	{
		FGlobalEventManager::TriggerEvent(FName("CardActiveEvent"), &CurrentActiveIndex);
	}
	else
	{
		// remove the Last value, add current value at head
		DisplayingIndex.RemoveAt(CardNum - 1);
		DisplayingIndex.Insert(CurrentActiveIndex, 0);
		
		auto *PendingWidget = SortCardsHorBox->GetChildAt(CardNum - 1);
		PendingWidget->RemoveFromParent();
		
		auto *FuncPtr = PendingWidget->FindFunction(FName("Init"));
		if (FuncPtr)
		{
			struct 
			{
				TEnumAsByte<EItemClassification> Index;
				FName ImageName;
			} Params;
			Params.Index = CurrentActiveIndex;
			Params.ImageName = CardImages.FindRef(CurrentActiveIndex);
			
			PendingWidget->ProcessEvent(FuncPtr, &Params);
		}

		TArray<UUserWidget*> OtherCards;
		OtherCards.Add(Cast<UUserWidget>(PendingWidget));
		for (auto Widget : SortCardsHorBox->GetAllChildren())
		{
			OtherCards.Add(Cast<UUserWidget>(Widget));
			Widget->RemoveFromParent();
		}

		for (auto OtherCard : OtherCards)
		{
			SortCardsHorBox->AddChildToHorizontalBox(OtherCard);
		}
		
		
		FGlobalEventManager::TriggerEvent(FName("CardActiveEvent"), &CurrentActiveIndex);
	}
}

void USortCardsType1::NativeRightButtonClicked()
{
	CurrentActiveIndex = TEnumAsByte<EItemClassification>((CurrentActiveIndex + 1) % TotalNum);
	// if the active index + 1, is still a displaying index
	if (DisplayingIndex.Contains(CurrentActiveIndex))
	{
		FGlobalEventManager::TriggerEvent(FName("CardActiveEvent"), &CurrentActiveIndex);
	}
	else
	{
		// remove the first value, add current value at tail
		DisplayingIndex.RemoveAt(0);
		DisplayingIndex.Add(CurrentActiveIndex);

		auto *PendingWidget = SortCardsHorBox->GetChildAt(0);
		PendingWidget->RemoveFromParent();
		
		auto *FuncPtr = PendingWidget->FindFunction(FName("Init"));
		if (FuncPtr)
		{
			struct 
			{
				TEnumAsByte<EItemClassification> Index;
				FName ImageName;
			} Params;
			Params.Index = CurrentActiveIndex;
			Params.ImageName = CardImages.FindRef(CurrentActiveIndex);
			
			PendingWidget->ProcessEvent(FuncPtr, &Params);
			SortCardsHorBox->AddChildToHorizontalBox(PendingWidget);
		}
		FGlobalEventManager::TriggerEvent(FName("CardActiveEvent"), &CurrentActiveIndex);
	}
}