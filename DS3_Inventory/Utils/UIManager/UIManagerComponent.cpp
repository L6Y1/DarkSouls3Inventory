// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManagerComponent.h"

#include "UIState.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


DEFINE_LOG_CATEGORY(LogUIManager);

void UUIManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	InitUIState();
}

void UUIManagerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UUIManagerComponent::InitUIState_Implementation()
{
	auto PC = UGameplayStatics::GetPlayerController(GetOwner(), 0);
	if (!PC->IsLocalPlayerController())
	{
		UE_LOG(LogUIManager, Display, TEXT("%s is not local playercontroller, skipping init UIStates"), *PC->GetName());
		return;
	}
	for (auto UI : UIStates)
	{
		auto Widget = CreateWidget<UUIState>(PC, UI.Value.Get(), UI.Key);

		UE_LOG(LogUIManager, Display, TEXT("初始化UI: %s"), *UI.Key.ToString());
		UIInstances.Add(UI.Key, Widget);
	}
}

UUIState * UUIManagerComponent::GetUI_Implementation(FName UIName)
{
	auto UI = UIInstances.Find(UIName);
	if (UI != nullptr)
	{
		return *UI;
	}

	UE_LOG(LogUIManager, Error, TEXT("UIManager 中不存在:%s"), *UIName.ToString())
	
	return nullptr;
}

void UUIManagerComponent::PushUIState(FName UIName)
{
	auto UI = GetUI(UIName);
	if (UI == nullptr) return;

	TScriptInterface<IStackStateInterface> Interface(UI);
	
	PushState(UI);
}

void UUIManagerComponent::GetCurrentUIState(TSubclassOf<UUIState> StateClass, TEnumAsByte<EUIStateCastResult> &IsValid,
	UUIState *&OutState)
{
	if (StateCount() <= 0)
	{
		IsValid = Failed;
		return;
	}

	UUIState *State = Cast<UUIState>(GetCurrentState().GetObject());
	IsValid = State != nullptr && State->GetClass()->IsChildOf(StateClass) ? Success : Failed;

	if (IsValid == Success)
	{
		OutState = State;
	}
	
}
