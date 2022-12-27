// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StateMachineTypes.generated.h"

UENUM(BlueprintType)
enum EStackAction { Push, Pop };

DECLARE_LOG_CATEGORY_EXTERN(LogStateMachine, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogStackStateMachine, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStateEnterSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStateExitSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStateUpdateSignature);
/**
 * 
 */
UCLASS()
class DS3_INVENTORY_API UStateMachineTypes : public UObject
{
	GENERATED_BODY()
	
};

