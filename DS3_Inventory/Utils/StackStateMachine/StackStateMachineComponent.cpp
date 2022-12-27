// Fill out your copyright notice in the Description page of Project Settings.


#include "StackStateMachineComponent.h"
#include "StateMachineTypes.h"

// Sets default values for this component's properties
UStackStateMachineComponent::UStackStateMachineComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStackStateMachineComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UStackStateMachineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (StateCount() > 0 && GetCurrentState() != nullptr)
	{
		GetCurrentState()->UpdateState(DeltaTime);
	}
}

void UStackStateMachineComponent::EnterState(EStackAction StackAction)
{
	if (OnStateEnter.IsBound())
	{
		OnStateEnter.Broadcast();
	}
	ReceiveEnterState(StackAction);
}

void UStackStateMachineComponent::ExitState(EStackAction StackAction)
{
	if (OnStateExit.IsBound())
	{
		OnStateExit.Broadcast();
	}
	ReceiveExitState(StackAction);
}

void UStackStateMachineComponent::UpdateState(float DeltaTime)
{
	ReceiveUpdateState(DeltaTime);
	CurrentStateTime += DeltaTime;
	if (StateCount() > 0)
	{
		GetCurrentState()->UpdateState(DeltaTime);
	}
}

void UStackStateMachineComponent::PushState(TScriptInterface<IStackStateInterface> NewState)
{
	if (StateCount() > 0)
	{
		auto CurrentState = GetCurrentState();
		if (CurrentState != nullptr)
		{
			CurrentState->ExitState(Push);
		}
	}

	CurrentStateTime = 0;
	States.Push(NewState);
	NewState->EnterState(Push);

	StatePushed(NewState);
}

void UStackStateMachineComponent::PopState()
{
	auto OriginState = GetCurrentState();
	if (OriginState != nullptr)
	{
		OriginState->ExitState(Pop);
	}

	States.Pop();
	CurrentStateTime = 0;
	if (StateCount() > 0)
	{
		GetCurrentState()->EnterState(Pop);
	}

	StatePopped(OriginState);
}

void UStackStateMachineComponent::PopStates(int Count)
{
	while (Count > 0)
	{
		PopState();
		--Count;
	}
}

void UStackStateMachineComponent::PopAllStates()
{
	PopStates(StateCount());
}

void UStackStateMachineComponent::StatePushed(TScriptInterface<IStackStateInterface> PushedState)
{
	UE_LOG(LogStackStateMachine, Display, TEXT("Pushed 状态: %s"), *PushedState.GetObject()->GetName());
	if (OnStatePushed.IsBound())
	{
		OnStatePushed.Broadcast(PushedState);
	}
	ReceiveStatePushed(PushedState);
}

void UStackStateMachineComponent::StatePopped(TScriptInterface<IStackStateInterface> PoppedState)
{
	UE_LOG(LogStackStateMachine, Display, TEXT("Popped 状态: %s"), *PoppedState.GetObject()->GetName());
	if (OnStatePopped.IsBound())
	{
		OnStatePopped.Broadcast(PoppedState);
	}
	ReceiveStatePopped(PoppedState);
}
