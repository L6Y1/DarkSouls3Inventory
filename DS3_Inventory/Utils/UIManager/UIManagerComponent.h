// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DS3_Inventory/Utils/StackStateMachine/StackStateMachineComponent.h"
#include "UIManagerComponent.generated.h"

class UUIState;
DECLARE_LOG_CATEGORY_EXTERN(LogUIManager, Log, All);

UENUM()
enum EUIStateCastResult { Success, Failed };


/**
 * 
 */
UCLASS()
class DS3_INVENTORY_API UUIManagerComponent : public UStackStateMachineComponent
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	TMap<FName, UUIState*> UIInstances;
	
public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
public:
	// config all UI and Corresponding Name in UnrealEditor, and init all UI in InitUIState()
	UPROPERTY(EditDefaultsOnly, Category = "UIManager")
	TMap<FName, TSubclassOf<UUIState>> UIStates;

	// init all ui
	UFUNCTION(BlueprintNativeEvent, Category = "UIManager")
	void InitUIState();

	// get ui instance by name in UIStates
	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "UIManager", meta=(DisplayName="GetUI"))
	UUIState* GetUI(FName UIName);

	UFUNCTION(BlueprintCallable, Category = "UIManager", meta=(DisplayName="PushUIState"))
	void PushUIState(FName UIName);

	UFUNCTION(BlueprintCallable, Category = "UIManager", meta=(ExpandEnumAsExecs="IsValid", DeterminesOutputType="StateClass", DynamicOutputParam="OutState"))
	void GetCurrentUIState(TSubclassOf<UUIState> StateClass, TEnumAsByte<EUIStateCastResult> &IsValid, UUIState *&OutState);
};
