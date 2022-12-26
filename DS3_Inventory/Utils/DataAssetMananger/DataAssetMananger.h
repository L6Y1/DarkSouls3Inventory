// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "InventoryDataAsset.h"
#include "Engine/DataAsset.h"
#include "Engine/StreamableManager.h"
#include "DataAssetMananger.generated.h"

UCLASS()
class  UInventoryDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<FName, TSoftObjectPtr<UObject>> SoftObjectPtrs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<FName, TSoftClassPtr<UObject>> SoftClassPtrs;
};



class FAsyncLoad {
public:
	TSharedPtr<FStreamableHandle> Handle;
};



UCLASS()
class  ADataAssetMananger : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		TArray<UInventoryDataAsset*> DataAssets;

	virtual void Destroyed()override;

private:
	static ADataAssetMananger* GetInst(UObject* Obj);
private:
	static FSoftObjectPath GetSoftObjectPathByName(UObject* Obj, FName AssetName);
	static TArray<FSoftObjectPath> GetSoftObjectPathsByNames(UObject* Obj, TArray<FName> AssetNames);
	static FSoftObjectPath GetSoftClassPathByName(UObject* Obj, FName AssetName);
public:
	//�첽����һ������(�ʲ�)  LoadObject
	static void RequestAsyncLoadObject(UObject* Obj, FName AssetName, TFunction<void(UObject* AssetObj)>&& Callback);
	//�첽���ض������(�ʲ�)  LoadObjects
	static void RequestAsyncLoadObjects(UObject* Obj, TArray<FName> AssetNames, TFunction<void(TArray<UObject*> AssetObjs)>&& Callback);

	//�첽����һ������(�ʲ�)  
	static void RequestAsyncLoadClass(UObject* Obj, FName AssetName, TFunction<void(UClass* ClassAsset)>&& Callback);
	//ͬ������һ������(�ʲ�) LoadClass
	static class UClass* RequestSyncLoadClass(UObject* Obj, FName AssetName);
private:
	FStreamableManager StreamableManager;

};



