// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GlobalEventManager.generated.h"

class FGlobalEventManager
{
	FGlobalEventManager() = default;
	
	static TSharedPtr<FGlobalEventManager> Instance;

	TMap<FName, TArray<FScriptDelegate>> Events;
	
public:
	// bind your function in a Object to a delegate
	static void RegisterEvent(FName EventName, UObject *Obj, FName FunctionName);

	// remove the function bind to the delegate 
	static void UnRegisterEvent(FName EventName, UObject *Obj);

	// call delegate
	static void TriggerEvent(FName EventName, void *Params);
	
	
	
	static TSharedPtr<FGlobalEventManager> GetInstance()
	{
		if (!Instance.IsValid())
		{
			Instance = MakeShareable(new FGlobalEventManager());
		}
		return Instance;
	}
};






/**
 * 
 */
UCLASS()
class UGlobalEventManager : public UObject
{
	GENERATED_BODY()
	
};
