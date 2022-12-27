// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StackStateInterface.h"
#include "UObject/NoExportTypes.h"
#include "StackState.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable, HideCategories = ("Cooking", "LOD", "Physics", "Activation", "Tags", "Rendering"))
class DS3_INVENTORY_API UStackState : public UObject, public IStackStateInterface
{
	GENERATED_BODY()

public:
	virtual void EnterState(EStackAction StackAction) override;
	virtual void ExitState(EStackAction StackAction) override;
	virtual void UpdateState(float DeltaTime) override;


	UFUNCTION(BlueprintImplementableEvent, Category="StackState", meta=(DisplayName = "OnEnterState"))
	void ReceiveEnterState(EStackAction StackAction);

	UFUNCTION(BlueprintImplementableEvent, Category="StackState", meta=(DisplayName = "OnExitState"))
	void ReceiveExitState(EStackAction StackAction);

	UFUNCTION(BlueprintImplementableEvent, Category="StackState", meta=(DisplayName = "OnUpdateState"))
	void ReceiveUpdateState(float DeltaTime);
};
