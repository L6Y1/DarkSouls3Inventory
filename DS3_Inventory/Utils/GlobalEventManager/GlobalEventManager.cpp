// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalEventManager.h"

TSharedPtr<FGlobalEventManager> FGlobalEventManager::Instance = nullptr;



void FGlobalEventManager::RegisterEvent(FName EventName, UObject *Obj, FName FunctionName)
{
	if (!GetInstance()->Events.Contains(EventName))
	{
		TArray<FScriptDelegate> Delegates;
		FScriptDelegate Delegate;
		
		Delegate.BindUFunction(Obj, FunctionName);
		Delegates.Add(Delegate);
		GetInstance()->Events.Add(EventName, Delegates);
		
	}
	else
	{
		FScriptDelegate Delegate;
		Delegate.BindUFunction(Obj, FunctionName);
		GetInstance()->Events.Find(EventName)->Add(Delegate);
	}
}

void FGlobalEventManager::UnRegisterEvent(FName EventName, UObject *Obj)
{
	if (GetInstance()->Events.Contains(EventName))
	{
		auto *Delegates = GetInstance()->Events.Find(EventName);
		for (int i = 0; i < Delegates->Num(); ++i)
		{
			if ((*Delegates)[i].GetUObject() == Obj)
			{
				(*Delegates)[i].Unbind();
				GetInstance()->Events.Find(EventName)->RemoveAt(i);
				--i;
			}
		}
		if (GetInstance()->Events.Find(EventName)->Num() == 0)
		{
			GetInstance()->Events.Remove(EventName);
		}
		
		
	}
	else
	{
		checkf(false, TEXT("Invalid EventName"));
	}
}

void FGlobalEventManager::TriggerEvent(FName EventName, void *Params)
{
	if (GetInstance()->Events.Contains(EventName))
	{
		auto Delegates= *GetInstance()->Events.Find(EventName);

		for (auto Delegate : Delegates)
		{
			if (Delegate.IsBound())
			{
				Delegate.ProcessDelegate<UObject>(Params);
			}
		}
		
		// for (int i = 0; i < Delegates.Num(); ++i)
		// {
		// 	if (IsValid(Delegates[i].GetUObject()))
		// 	{
		// 		Delegates[i].ProcessDelegate<UObject>(Params);
		// 	}
		// 	else
		// 	{
		// 		Delegates.RemoveAt(i);
		// 		--i;
		// 	}
		// }
	}
}
