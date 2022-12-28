// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DS3_Inventory/Utils/StackStateMachine/StackStateInterface.h"
#include "UIState.generated.h"

/**
 * 
 */
UCLASS()
class DS3_INVENTORY_API UUIState : public UUserWidget, public IStackStateInterface
{
	GENERATED_BODY()

public:
	virtual void EnterState(EStackAction StackAction) override;
	virtual void ExitState(EStackAction StackAction) override;
	virtual void UpdateState(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, Category="StackState", meta=(DisplayName="OnEnterState"))
	void ReceiveEnterState(EStackAction StackAction);
	
	UFUNCTION(BlueprintNativeEvent, Category="StackState", meta=(DisplayName="OnExitState"))
	void ReceiveExitState(EStackAction StackAction);
	
	UFUNCTION(BlueprintNativeEvent, Category="StackState", meta=(DisplayName="OnUpdateState"))
	void ReceiveUpdateState(float DeltaTime);
};
