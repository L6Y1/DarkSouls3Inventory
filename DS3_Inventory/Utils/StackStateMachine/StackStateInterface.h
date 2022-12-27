// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateMachineTypes.h"
#include "UObject/Interface.h"
#include "StackStateInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))
class UStackStateInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DS3_INVENTORY_API IStackStateInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// when you execute this function, the param specifies what action the state machine is taking -- push or pop
	virtual void EnterState(EStackAction StackAction) = 0;
	virtual void ExitState(EStackAction StackAction) = 0;
	virtual void UpdateState(float DeltaTime) = 0;
};
