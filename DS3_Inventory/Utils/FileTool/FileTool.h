// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DS3_Inventory/Utils/StructTypes.h"
#include "FileTool.generated.h"


/**
 * @brief util class for FFileTool to serialize/deserialize JSON string 
 */
class FJsonTool
{
private:
	// JSON string to GameSaveData
	static FGameSaveData GetGameSaveDataFromJsonStr(FString JsonStr);

	// GameSaveData to JSON string
	static FString GetJsonStrFromGameSaveData(FGameSaveData GameSaveData);

	friend class FFileTool;
};

/**
 * @brief util class, can save FGameSaveData to file / read file to get FGameSaveData
 */
class FFileTool
{
private:
	// util function
	// save str to file
	static bool SaveStrToFile(FString InString, FString RelativePath, FString FileName);
	
	// read str from file
	static bool LoadStrFromFile(FString &OutString, FString RelativePath, FString FileName);


public:
	// load game
	static FGameSaveData LoadGame(FString RelativePath = FString("/GameSaves"),
		FString FileName = FString("SaveGame00.sav"));
	
	// save game
	static void SaveGame(FGameSaveData InGameSaveData,
		FString RelativePath = FString("/GameSaves"),
		FString FileName = FString("SaveGame00.sav"));
	
};

class FGameSaveTool
{
public:
	static FORCEINLINE FGameSaveData GetGameSaveData()
	{
		return FFileTool::LoadGame();
	}

	/**
	 * @brief 
	 * @param Classification the classification of item wished to be found
	 * @param Index the index of item to be found
	 * @return grid data of the item
	 */
	static FGridData GetClassifiedGridDataByIndex(TEnumAsByte<EItemClassification> Classification, int Index);

	/**
	 * @brief 
	 * @param Classification the classification
	 * @return item number of given classification
	 */
	static int GetTotalItemNumberByClassification(TEnumAsByte<EItemClassification> Classification);

	// save a single grid/storage grid
	static void SaveGrid(int Index, FGridData GridData);
	static void SaveStorageGrid(int Index, FGridData GridData);

	static TMap<FName, FItemOnGroundData> GetItemOnGroundDatas();
	static FItemOnGroundData GetItemOnGroundDataByIndex(FName Index);

	static void SetItemOnGroundDataByIndex(FName Index, FItemOnGroundData NewData);
	static void RemoveItemOnGroundDataByIndex(const FName &Index);
	static bool ItemOnGroundExist(FName Index);
	static void AddItemOnGroundData(FName Index, FItemOnGroundData NewData);
	
};


/**
 * 
 */
UCLASS()
class DS3_INVENTORY_API UFileTool : public UObject
{
	GENERATED_BODY()
	
};
