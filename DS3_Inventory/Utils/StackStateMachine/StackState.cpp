// Fill out your copyright notice in the Description page of Project Settings.


#include "StackState.h"

void UStackState::EnterState(EStackAction StackAction)
{
	ReceiveEnterState(StackAction);
}

void UStackState::ExitState(EStackAction StackAction)
{
	ReceiveExitState(StackAction);
}

void UStackState::UpdateState(float DeltaTime)
{
	ReceiveUpdateState(DeltaTime);
}
