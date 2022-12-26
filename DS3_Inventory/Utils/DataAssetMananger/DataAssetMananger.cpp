// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssetMananger.h"
#include "Kismet/GameplayStatics.h"
//ADataAssetMananger* ADataAssetMananger::Inst=NULL;

void ADataAssetMananger::Destroyed()
{
	Super::Destroyed();
	//if (Inst) {
	//	Inst->DataAssets.Empty();
	//	Inst = NULL;
	//}

}

ADataAssetMananger * ADataAssetMananger::GetInst(UObject* Obj)
{
	//if (Inst == NULL)
	//{
	ADataAssetMananger * Inst = NULL;
	TArray<AActor*> OutActorArray;
	UGameplayStatics::GetAllActorsOfClass(Obj, ADataAssetMananger::StaticClass(), OutActorArray);
	checkf(OutActorArray.Num() == 1, TEXT("ADataAssetMananger Obj Only One In Scene"));
	Inst = Cast<ADataAssetMananger>(OutActorArray[0]);
	//}
	check(Inst);
	return Inst;
}

FSoftObjectPath ADataAssetMananger::GetSoftObjectPathByName(UObject* Obj, FName AssetName)
{
	FSoftObjectPath SoftObjectPath;
	ADataAssetMananger* Inst = ADataAssetMananger::GetInst(Obj);
	check(Inst);
	check(Inst->DataAssets.Num() != 0);
	for (UInventoryDataAsset* DataAsset : Inst->DataAssets)
	{
		check(DataAsset);
		if (DataAsset)
		{
			check(DataAsset->SoftObjectPtrs.Num() != 0);
			if (DataAsset->SoftObjectPtrs.Contains(AssetName))
			{
				SoftObjectPath = (DataAsset->SoftObjectPtrs[AssetName].ToSoftObjectPath());
				break;
			}
		}
	}

	checkf(SoftObjectPath.IsValid(), TEXT("Cant Find ObjectAsset : %s"), *(AssetName.ToString()));
	return SoftObjectPath;
}

TArray<FSoftObjectPath> ADataAssetMananger::GetSoftObjectPathsByNames(UObject * Obj, TArray<FName> AssetNames)
{
	TArray<FSoftObjectPath> SoftObjectPaths;
	for (FName AssetName : AssetNames)
	{
		SoftObjectPaths.Add(GetSoftObjectPathByName(Obj, AssetName));
	}
	return SoftObjectPaths;
}

FSoftObjectPath  ADataAssetMananger::GetSoftClassPathByName(UObject * Obj, FName AssetName)
{
	FSoftObjectPath SoftObjectPath;

	ADataAssetMananger* Inst = ADataAssetMananger::GetInst(Obj);
	check(Inst);
	check(Inst->DataAssets.Num() != 0);
	for (UInventoryDataAsset* DataAsset : Inst->DataAssets)
	{
		check(DataAsset);
		if (DataAsset)
		{
			check(DataAsset->SoftClassPtrs.Num() != 0);
			if (DataAsset->SoftClassPtrs.Contains(AssetName))
			{
				SoftObjectPath = (DataAsset->SoftClassPtrs[AssetName].ToSoftObjectPath());
				break;
			}
		}
	}
	checkf(SoftObjectPath.IsValid(), TEXT("Cant Find ClassAsset : %s"), *(AssetName.ToString()));
	return SoftObjectPath;
}

#include "Kismet/KismetSystemLibrary.h"

void ADataAssetMananger::RequestAsyncLoadObject(UObject * Obj, FName AssetName, TFunction<void(UObject* AssetObj)>&& Callback)
{
	FSoftObjectPath Path = GetSoftObjectPathByName(Obj, AssetName);

	ADataAssetMananger* Inst = ADataAssetMananger::GetInst(Obj);
	FAsyncLoad* AsyncLoad = new FAsyncLoad();

	AsyncLoad->Handle
		= ADataAssetMananger::GetInst(Obj)->StreamableManager.RequestAsyncLoad(
			Path,
			[Inst, AsyncLoad, Callback, Obj]()
	{
		//UKismetSystemLibrary::PrintString(Obj, TEXT(__FUNCTION__), true, false, FColor::Green, 100);

		check(AsyncLoad->Handle);
		UObject* AssetObj = AsyncLoad->Handle->GetLoadedAsset();
		check(AssetObj);

		Callback(AssetObj);
		delete 	AsyncLoad;
	}
	);



}

void ADataAssetMananger::RequestAsyncLoadObjects(UObject* Obj, TArray<FName> AssetNames, TFunction<void(TArray<UObject*> AssetObjs)>&& Callback) {
	TArray<FSoftObjectPath> Paths = GetSoftObjectPathsByNames(Obj, AssetNames);

	if (Paths.Num() != 0)
	{
		ADataAssetMananger* Inst = ADataAssetMananger::GetInst(Obj);
		FAsyncLoad* AsyncLoad = new FAsyncLoad();
		AsyncLoad->Handle = ADataAssetMananger::GetInst(Obj)->StreamableManager.RequestAsyncLoad(
			Paths,
			[Inst, AsyncLoad, Callback, Obj]()
		{
			check(AsyncLoad->Handle);
			TArray<UObject*> AssetObjs;
			AsyncLoad->Handle->GetLoadedAssets(AssetObjs);
			check(AssetObjs.Num() != 0);
			Callback(AssetObjs);
			delete 	AsyncLoad;
		}
		);
	}
}

void ADataAssetMananger::RequestAsyncLoadClass(UObject * Obj, FName AssetName, TFunction<void(UClass* ClassAsset)>&& Callback)
{
	FSoftObjectPath  Path = GetSoftClassPathByName(Obj, AssetName);

	ADataAssetMananger* Inst = ADataAssetMananger::GetInst(Obj);
	FAsyncLoad* AsyncLoad = new FAsyncLoad();
	AsyncLoad->Handle = ADataAssetMananger::GetInst(Obj)->StreamableManager.RequestAsyncLoad(
		Path,
		[Inst, AsyncLoad, Callback, Obj]()
	{
		//UKismetSystemLibrary::PrintString(Obj, TEXT(__FUNCTION__), true, false, FColor::Green, 100);
		check(AsyncLoad->Handle);
		UClass* AssetClass = Cast<UClass>(AsyncLoad->Handle->GetLoadedAsset());
		check(AssetClass);

		Callback(AssetClass);
		delete 	AsyncLoad;
	}
	);


}

UClass * ADataAssetMananger::RequestSyncLoadClass(UObject * Obj, FName AssetName)
{
	FSoftObjectPath  Path = GetSoftClassPathByName(Obj, AssetName);
	ADataAssetMananger* Inst = ADataAssetMananger::GetInst(Obj);

	return Cast<UClass>(Inst->StreamableManager.RequestSyncLoad(Path)->GetLoadedAsset());
}
