// Fill out your copyright notice in the Description page of Project Settings.


#include "DS3_InventoryPC.h"
#include "Blueprint/UserWidget.h"
#include "DS3_Inventory/Utils/GlobalEventManager/GlobalEventManager.h"
#include "GameFramework/PlayerInput.h"

ADS3_InventoryPC::ADS3_InventoryPC()
{
	// get UClass of main ui
	ConstructorHelpers::FClassFinder<UUserWidget> MainUIClassFinder(TEXT("WidgetBlueprint'/Game/Blueprints/UI/BP_MainUI.BP_MainUI_C'"));
	if (MainUIClassFinder.Succeeded())
	{
		MainUIClass = MainUIClassFinder.Class;
	}
}

void ADS3_InventoryPC::BeginPlay()
{
	Super::BeginPlay();
	
	// create main ui
	checkf(MainUIClass, TEXT("MainUIClass not found, check file path"));
	MainUIWidget = CreateWidget(this, MainUIClass);

	const auto FuncPtr = MainUIWidget->FindFunction(FName("Init"));
	if (FuncPtr)
	{
		MainUIWidget->ProcessEvent(FuncPtr, nullptr);
	}
	
	MainUIWidget->AddToViewport();
}

void ADS3_InventoryPC::SetupInputComponent()
{
	Super::SetupInputComponent();
	UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(FName("ToggleMenuTop"), EKeys::Tab));

	InputComponent->BindAction(FName("ToggleMenuTop"), IE_Pressed, this, &ADS3_InventoryPC::ToggleMenuTop);
}

void ADS3_InventoryPC::ToggleMenuTop()
{
	FGlobalEventManager::TriggerEvent(FName("ToggleMenuTopEvent"), nullptr);
	
}
