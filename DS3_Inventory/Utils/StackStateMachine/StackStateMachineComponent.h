// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StackStateInterface.h"
#include "Components/ActorComponent.h"
#include "StackStateMachineComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStackPushPopSignature, TScriptInterface<IStackStateInterface>, State);

/**
 *	栈状态机组件，主要维护一个用作栈的集合，用于管理所有的状态，能进行压栈和出栈操作
 *	栈状态机本身也是一种状态，也可以进入，退出，更新
 *
 *	StackStateMachine Component maintains a TArray(used as a stack) of States,
 *	and manage them, it can push or pop states. Meanwhile the StackStateMachine itself
 *	is also a state, which can be entered, exited, updated
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DS3_INVENTORY_API UStackStateMachineComponent : public UActorComponent, public IStackStateInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStackStateMachineComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// StackStateMachine as a state
	virtual void EnterState(EStackAction StackAction) override;
	virtual void ExitState(EStackAction StackAction) override;
	virtual void UpdateState(float DeltaTime) override;

	// push a state to stack
	UFUNCTION(BlueprintCallable, Category = "StackStateMachine")
	void PushState(TScriptInterface<IStackStateInterface> NewState);

	// pop a state from stack
	UFUNCTION(BlueprintCallable, Category = "StackStateMachine")
	void PopState();

	// pop 'Count' states from stack
	UFUNCTION(BlueprintCallable, Category = "StackStateMachine")
	void PopStates(int Count);

	// pop all states from stack
	UFUNCTION(BlueprintCallable, Category = "StackStateMachine")
	void PopAllStates();
	
public:
	// blueprint callbacks
	UFUNCTION(BlueprintImplementableEvent, Category = "StackStateMachine", meta=(DisplayName = "OnEnterState"))
	void ReceiveEnterState(EStackAction StackAction);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "StackStateMachine", meta=(DisplayName = "OnExitState"))
	void ReceiveExitState(EStackAction StackAction);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "StackStateMachine", meta=(DisplayName = "OnUpdateState"))
	void ReceiveUpdateState(float DeltaTime);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "StackStateMachine", meta=(DisplayName = "StatePushed"))
	void ReceiveStatePushed(TScriptInterface<IStackStateInterface> &PushedState);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "StackStateMachine", meta=(DisplayName = "StatePopped"))
	void ReceiveStatePopped(TScriptInterface<IStackStateInterface> &PoppedState);


	UPROPERTY(BlueprintAssignable, Category="StackStateMachine")
	FOnStateEnterSignature OnStateEnter;
	
	UPROPERTY(BlueprintAssignable, Category="StackStateMachine")
	FOnStateExitSignature OnStateExit;
	
	UPROPERTY(BlueprintAssignable, Category="StackStateMachine")
	FOnStackPushPopSignature OnStatePushed;
	
	UPROPERTY(BlueprintAssignable, Category="StackStateMachine")
	FOnStackPushPopSignature OnStatePopped;

	// setters and getters
	UFUNCTION(BlueprintPure, Category = "StackStateMachine")
	TScriptInterface<IStackStateInterface> GetCurrentState() { return States[StateCount() - 1]; }

	UFUNCTION(BlueprintPure, Category = "StackStateMachine")
	TScriptInterface<IStackStateInterface> GetUnderState() { return StateCount() - 2 >= 0 ? States[StateCount() - 2] : nullptr ; }
	
	UFUNCTION(BlueprintPure, Category = "StackStateMachine")
	TScriptInterface<IStackStateInterface> GetState(int Index) { return States[Index]; }
	
	UFUNCTION(BlueprintPure, Category = "StackStateMachine")
	int32 StateCount() const { return States.Num(); }

	UFUNCTION(BlueprintPure, Category = "StackStateMachine")
	FORCEINLINE float GetCurrentStateTime() const { return CurrentStateTime; }

	
protected:
	// state pushed/popped successfully
	virtual void StatePushed(TScriptInterface<IStackStateInterface> PushedState);
	virtual void StatePopped(TScriptInterface<IStackStateInterface> PoppedState);

	// stack that stores all states in the state machine
	TArray<TScriptInterface<IStackStateInterface>> States;

	// current state duration
	UPROPERTY(VisibleAnywhere)
	float CurrentStateTime = 0;
};