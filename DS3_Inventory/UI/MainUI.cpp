// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"
#include "Components/NamedSlot.h"
#include "DS3_Inventory/GameMode/DS3_InventoryPC.h"
#include "DS3_Inventory/Utils/DataAssetMananger/DataAssetMananger.h"
#include "DS3_Inventory/Utils/DataTableTool/DataTableTool.h"
#include "DS3_Inventory/Utils/GlobalEventManager/GlobalEventManager.h"
#include "DS3_Inventory/Utils/UIManager/UIManagerComponent.h"


void UMainUI::NativeConstruct()
{
	Super::NativeConstruct();
	FGlobalEventManager::RegisterEvent(FName("ToggleMenuTopEvent"), this, FName("ToggleMenuTop"));
}

void UMainUI::NativeDestruct()
{
	Super::NativeDestruct();
	FGlobalEventManager::UnRegisterEvent(FName("ToggleMenuTopEvent"), this);
}

void UMainUI::Init()
{
	// TODO: init quickBar
}

void UMainUI::ToggleMenuTop()
{
	if (Cast<ADS3_InventoryPC>(GetOwningPlayer())->UIManagerComponent->GetCurrentState() == this)
	{
		FString MenuTopTypeStr;
		GConfig->GetString(
			TEXT("GameUIInit/MainUI/MenuTop"),
			TEXT("MenuTopType"),
			MenuTopTypeStr,
			GGameIni
		);

		FString MenuTopSkinTypeStr;
		GConfig->GetString(
			TEXT("GameUIInit/MainUI/MenuTop"),
			TEXT("MenuTopSkinType"),
			MenuTopSkinTypeStr,
			GGameIni
		);
		auto *MenuTopType1Attr = FDataTableTool::GetMenuTopType1Attr(FName(MenuTopSkinTypeStr));

		
		ADataAssetMananger::RequestAsyncLoadClass(this, FName(MenuTopTypeStr),
			[this, MenuTopType1Attr](UClass *ClassAsset)
			{
				const auto MenuTopWidget = CreateWidget(this->GetOwningPlayer(), ClassAsset);
				
				// init MenuTop
				const auto FuncPtr = MenuTopWidget->FindFunction(FName("Init"));
				if (FuncPtr)
				{
					MenuTopWidget->ProcessEvent(FuncPtr, MenuTopType1Attr);
				}

				Cast<ADS3_InventoryPC>(GetOwningPlayer())->UIManagerComponent->PushState(MenuTopWidget);
			}
		);
	}
	else
	{
		Cast<ADS3_InventoryPC>(GetOwningPlayer())->UIManagerComponent->PopState();
	}
}
