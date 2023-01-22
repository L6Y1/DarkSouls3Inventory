// Fill out your copyright notice in the Description page of Project Settings.


#include "FileTool.h"

#include "JsonObjectConverter.h"

#include "Kismet/KismetSystemLibrary.h"

FGameSaveData FFileTool::LoadGame(FString RelativePath, FString FileName)
{
	FGameSaveData GameSaveData;
	FString OutJsonStr;
	if (LoadStrFromFile(OutJsonStr, RelativePath, FileName))
	{
		GameSaveData = FJsonTool::GetGameSaveDataFromJsonStr(OutJsonStr);
	}
	else
	{
		FPlayerData PlayerData;
		// get data from game.ini
		// ...

		PlayerData.Name = "Alice";
		PlayerData.Location = FVector(-770, 370, 226);
		PlayerData.PlayerStats.Level = 10;
		PlayerData.PlayerStats.Curse = 0;
		PlayerData.PlayerStats.MaxHP = 500;
		PlayerData.PlayerStats.CurrentHP = 500;
		PlayerData.PlayerStats.MaxFP = 20;
		PlayerData.PlayerStats.CurrentFP = 20;
		PlayerData.PlayerStats.MaxStamina = 50;
		PlayerData.PlayerStats.MaxEquipLoad = 40;
		PlayerData.PlayerStats.Poise = 15;
		PlayerData.PlayerStats.ItemDiscovery = 20;
		PlayerData.PlayerStats.AttunementSlots = 1;

		for (int i = 0; i <= 8; ++i)
		{
			PlayerData.PlayerStats.Stats.Add(TEnumAsByte<EPlayerStats>(i), 10);
		}
		
		FClassifiedGridData Data1, Data2;
		Data1.ClassifiedGridDataArray.Add(FGridData(10001, 3));
		Data1.ClassifiedGridDataArray.Add(FGridData(10002, 1));
		Data2.ClassifiedGridDataArray.Add(FGridData(20001, 1));
		
		PlayerData.InventoryData.GridDatas.Add(TEnumAsByte<EItemClassification>(0), Data1);
		PlayerData.InventoryData.GridDatas.Add(TEnumAsByte<EItemClassification>(1), Data2);
		PlayerData.InventoryData.GridDatas.Add(TEnumAsByte<EItemClassification>(2), FClassifiedGridData());
		PlayerData.InventoryData.GridDatas.Add(TEnumAsByte<EItemClassification>(3), FClassifiedGridData());
		PlayerData.InventoryData.GridDatas.Add(TEnumAsByte<EItemClassification>(4), FClassifiedGridData());
		PlayerData.InventoryData.GridDatas.Add(TEnumAsByte<EItemClassification>(5), FClassifiedGridData());

		for (int i = 0; i <= 5; ++i)
		{
			PlayerData.InventoryData.StorageGridDatas.Add(
				TEnumAsByte<EItemClassification>(i),
				FClassifiedStorageGridData());
		}
		
		GameSaveData.ItemOnGroundData.Add(FName("Item_0"),
		                                  FItemOnGroundData(FName("Item_0"), FVector(-900,240,200), 10003, 4));
		GameSaveData.ItemOnGroundData.Add(FName("Item_1"),
		                                  FItemOnGroundData(FName("Item_1"), FVector(-900,140,200), 20002, 1));
		SaveGame(GameSaveData, RelativePath, FileName);
	}
	return GameSaveData;
}

void FFileTool::SaveGame(FGameSaveData InGameSaveData, FString RelativePath, FString FileName)
{
	auto JsonStr = FJsonTool::GetJsonStrFromGameSaveData(InGameSaveData);
	SaveStrToFile(JsonStr, RelativePath, FileName);
}

bool FFileTool::SaveStrToFile(FString InString, FString RelativePath, FString FileName)
{
	if (!InString.IsEmpty() && !FileName.IsEmpty())
	{
		const auto AbsolutePath =
			FPaths::ProjectSavedDir() + RelativePath + FString("/") + FileName;
		if (FFileHelper::SaveStringToFile(InString, *AbsolutePath))
		{
			return true;
		}
	}
	
	return false;
}

bool FFileTool::LoadStrFromFile(FString &OutString, FString RelativePath, FString FileName)
{
	const auto AbsolutePath =
		FPaths::ProjectSavedDir() + RelativePath + FString("/") + FileName;
	if (!FileName.IsEmpty() && !AbsolutePath.IsEmpty())
	{
		if (FPaths::FileExists(AbsolutePath))
		{
			if (FFileHelper::LoadFileToString(OutString, *AbsolutePath))
			{
				return true;
			}
		}
	}

	return false;
}

FGameSaveData FJsonTool::GetGameSaveDataFromJsonStr(FString JsonStr)
{
	FGameSaveData GameSaveData;

	
	TSharedPtr<FJsonValue> JsonValue;
	auto JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonStr);

	
	if (FJsonSerializer::Deserialize(JsonReader, JsonValue))
	{
		// GameSaveData
		auto GameSaveDataJsonObj = JsonValue->AsObject();

		// GameSaveData.PlayerData
		{
			auto PlayerDataJsonObj =
            			GameSaveDataJsonObj->GetObjectField("PlayerData");
			checkf(PlayerDataJsonObj.IsValid(), TEXT("PlayerDataJsonObj is invalid"));

			// GameSaveData.PlayerData.Name
			GameSaveData.PlayerData.Name = FName(PlayerDataJsonObj->GetStringField(FString("Name")));

			// GameSaveData.PlayerData.Location
			auto LocationJsonValueArray = PlayerDataJsonObj->GetArrayField("Location");
			GameSaveData.PlayerData.Location = FVector(
				LocationJsonValueArray[0]->AsNumber(),
				LocationJsonValueArray[1]->AsNumber(),
				LocationJsonValueArray[2]->AsNumber()
			);

			// GameSaveData.PlayerData.PlayerStats
			{
				auto PlayerStatsJsonObj =
					PlayerDataJsonObj->GetObjectField("PlayerStats");

				GameSaveData.PlayerData.PlayerStats.Level = PlayerStatsJsonObj->GetIntegerField("Level");
				GameSaveData.PlayerData.PlayerStats.Curse = PlayerStatsJsonObj->GetIntegerField("Curse");
				GameSaveData.PlayerData.PlayerStats.MaxHP = PlayerStatsJsonObj->GetIntegerField("MaxHP");
				GameSaveData.PlayerData.PlayerStats.CurrentHP = PlayerStatsJsonObj->GetIntegerField("CurrentHP");
				GameSaveData.PlayerData.PlayerStats.MaxFP = PlayerStatsJsonObj->GetIntegerField("MaxFP");
				GameSaveData.PlayerData.PlayerStats.CurrentFP = PlayerStatsJsonObj->GetIntegerField("CurrentFP");
				GameSaveData.PlayerData.PlayerStats.MaxStamina = PlayerStatsJsonObj->GetIntegerField("MaxStamina");
				
				GameSaveData.PlayerData.PlayerStats.MaxEquipLoad = PlayerStatsJsonObj->GetIntegerField("MaxEquipLoad");
				GameSaveData.PlayerData.PlayerStats.Poise = PlayerStatsJsonObj->GetIntegerField("Poise");
				GameSaveData.PlayerData.PlayerStats.ItemDiscovery = PlayerStatsJsonObj->GetIntegerField("ItemDiscovery");
				GameSaveData.PlayerData.PlayerStats.AttunementSlots = PlayerStatsJsonObj->GetIntegerField("AttunementSlots");

				auto StatsJsonValueArray =
					PlayerStatsJsonObj->GetArrayField("Stats");
				
				auto StatJsonObj = StatsJsonValueArray[0]->AsObject();
				for (auto StatJsonValue : StatsJsonValueArray)
				{
					StatJsonObj = StatJsonValue->AsObject();
					GameSaveData.PlayerData.PlayerStats.Stats.Add(
						TEnumAsByte<EPlayerStats>(StatJsonObj->GetIntegerField("StatsEnumValue")),
						StatJsonObj->GetIntegerField("Value"));
				}
			}

			// GameSaveData.PlayerData.InventoryData
			{
				auto InventoryDataJsonObj =
					PlayerDataJsonObj->GetObjectField("InventoryData");

				// GameSaveData.PlayerData.InventoryData.GridDatas
				auto GirdDatasJsonValueArray = InventoryDataJsonObj->GetArrayField("GridDatas");

				// get each key-value pair in GameSaveData.PlayerData.InventoryData.GridDatas
				for (auto GridDataJsonValue : GirdDatasJsonValueArray)
				{
					auto GridDataJsonObj = GridDataJsonValue->AsObject();

					// key
					TEnumAsByte<EItemClassification> Key = TEnumAsByte<EItemClassification>(GridDataJsonObj->GetIntegerField("ItemClassificationEnumValue"));
					
					// value
					FClassifiedGridData Value;
					
					auto ClassifiedGridDataJsonValueArray = GridDataJsonObj->GetArrayField("ClassifiedGridData");
					
					for (auto ClassifiedGridDataJsonValue : ClassifiedGridDataJsonValueArray)
					{
						auto ClassifiedGridDataJsonObj = ClassifiedGridDataJsonValue->AsObject();
						int ItemID = ClassifiedGridDataJsonObj->GetIntegerField("ID");
						int ItemNum = ClassifiedGridDataJsonObj->GetIntegerField("Num");

						auto TempGridData = FGridData(ItemID, ItemNum);
						Value.ClassifiedGridDataArray.Add(TempGridData);
					}
					
					GameSaveData.PlayerData.InventoryData.GridDatas.Add(Key,Value);
				}
				
				// GameSaveData.PlayerData.InventoryData.StorageGridDatas
				auto StorageGridDatasJsonValueArray = InventoryDataJsonObj->GetArrayField("StorageGridDatas");
				
				// get each key-value pair in GameSaveData.PlayerData.InventoryData.StorageGridDatas
				for (auto StorageGridDataJsonValue : StorageGridDatasJsonValueArray)
				{
					auto StorageGridDataJsonObj = StorageGridDataJsonValue->AsObject();

					// key
					TEnumAsByte<EItemClassification> Key = TEnumAsByte<EItemClassification>(StorageGridDataJsonObj->GetIntegerField("ItemClassificationEnumValue"));
					
					// value
					FClassifiedStorageGridData Value;
					
					auto ClassifiedGridDataJsonValueArray = StorageGridDataJsonObj->GetArrayField("ClassifiedStorageGridData");
					
					for (auto ClassifiedGridDataJsonValue : ClassifiedGridDataJsonValueArray)
					{
						auto ClassifiedGridDataJsonObj = ClassifiedGridDataJsonValue->AsObject();
						int ItemID = ClassifiedGridDataJsonObj->GetIntegerField("ID");
						int ItemNum = ClassifiedGridDataJsonObj->GetIntegerField("Num");

						auto TempGridData = FGridData(ItemID, ItemNum);
						Value.ClassifiedStorageGridDataArray.Add(TempGridData);
					}
					
					GameSaveData.PlayerData.InventoryData.StorageGridDatas.Add(Key,Value);
				}
			}
		}
		
		
		// GameSaveData.ItemOnGroundData
		{
			auto ItemOnGroundDataJsonValueArray =
				GameSaveDataJsonObj->GetArrayField(FString("ItemOnGroundData"));

			for (auto OnGroundDataJsonValue : ItemOnGroundDataJsonValueArray)
			{
				auto OnGroundDataJsonObj = OnGroundDataJsonValue->AsObject();

				FName Key = FName(OnGroundDataJsonObj->GetStringField("Index"));
				FItemOnGroundData Value;
				
				auto LocationJsonValueArray = OnGroundDataJsonObj->GetArrayField("Location");
				Value.ItemOnGroundIndex = Key;
				Value.Location = FVector(
					LocationJsonValueArray[0]->AsNumber(),
					LocationJsonValueArray[1]->AsNumber(),
					LocationJsonValueArray[2]->AsNumber()					
				);
				Value.ID = OnGroundDataJsonObj->GetIntegerField("ID");
				Value.Num = OnGroundDataJsonObj->GetIntegerField("Num");
				GameSaveData.ItemOnGroundData.Add(Key, Value);
			}
			
		}
		
	}

	return GameSaveData;
}

FString FJsonTool::GetJsonStrFromGameSaveData(FGameSaveData GameSaveData)
{
	FString JsonStr;

	auto JsonWriter =
		TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&JsonStr);

	JsonWriter->WriteObjectStart();
	{
		// PlayerData
		JsonWriter->WriteIdentifierPrefix("PlayerData");
		JsonWriter->WriteObjectStart();
		{
			JsonWriter->WriteValue<FString>("Name", GameSaveData.PlayerData.Name.ToString());
			
			JsonWriter->WriteIdentifierPrefix("Location");
			JsonWriter->WriteArrayStart();
			JsonWriter->WriteValue<float>(GameSaveData.PlayerData.Location.X);
			JsonWriter->WriteValue<float>(GameSaveData.PlayerData.Location.Y);
			JsonWriter->WriteValue<float>(GameSaveData.PlayerData.Location.Z);
			JsonWriter->WriteArrayEnd();

			// PlayerData.PlayerStats
			JsonWriter->WriteIdentifierPrefix("PlayerStats");
			JsonWriter->WriteObjectStart();
			{
				JsonWriter->WriteValue<int>("Level", GameSaveData.PlayerData.PlayerStats.Level);
				JsonWriter->WriteValue<int>("Curse", GameSaveData.PlayerData.PlayerStats.Curse);
				JsonWriter->WriteValue<int>("MaxHP", GameSaveData.PlayerData.PlayerStats.MaxHP);
				JsonWriter->WriteValue<int>("CurrentHP", GameSaveData.PlayerData.PlayerStats.CurrentHP);
				JsonWriter->WriteValue<int>("MaxFP", GameSaveData.PlayerData.PlayerStats.MaxFP);
				JsonWriter->WriteValue<int>("CurrentFP", GameSaveData.PlayerData.PlayerStats.CurrentFP);
				JsonWriter->WriteValue<int>("MaxStamina", GameSaveData.PlayerData.PlayerStats.MaxStamina);

				// PlayerData.PlayerStats.Stats
				JsonWriter->WriteIdentifierPrefix("Stats");
				JsonWriter->WriteArrayStart();
				{
					for (auto KeyValuePair : GameSaveData.PlayerData.PlayerStats.Stats)
					{
						JsonWriter->WriteObjectStart();
						JsonWriter->WriteValue<int>("StatsEnumValue", KeyValuePair.Key);
						JsonWriter->WriteValue<int>("Value", KeyValuePair.Value);
						JsonWriter->WriteObjectEnd();
					}
				}
				JsonWriter->WriteArrayEnd();

				JsonWriter->WriteValue<int>("MaxEquipLoad", GameSaveData.PlayerData.PlayerStats.MaxEquipLoad);
				JsonWriter->WriteValue<int>("Poise", GameSaveData.PlayerData.PlayerStats.Poise);
				JsonWriter->WriteValue<int>("ItemDiscovery", GameSaveData.PlayerData.PlayerStats.ItemDiscovery);
				JsonWriter->WriteValue<int>("AttunementSlots", GameSaveData.PlayerData.PlayerStats.AttunementSlots);
			}
			JsonWriter->WriteObjectEnd();

			// PlayerData.InventoryData
			JsonWriter->WriteIdentifierPrefix("InventoryData");
			JsonWriter->WriteObjectStart();
			{
				// PlayerData.InventoryData.GridDatas
				JsonWriter->WriteIdentifierPrefix("GridDatas");
				JsonWriter->WriteArrayStart();
				{
					for (auto KeyValuePair : GameSaveData.PlayerData.InventoryData.GridDatas)
					{
						JsonWriter->WriteObjectStart();
						
						JsonWriter->WriteValue<int>("ItemClassificationEnumValue", KeyValuePair.Key);
						
						JsonWriter->WriteIdentifierPrefix("ClassifiedGridData");
						JsonWriter->WriteArrayStart();
						for (auto GridData : KeyValuePair.Value.ClassifiedGridDataArray)
						{
							JsonWriter->WriteObjectStart();
							JsonWriter->WriteValue<int>("ID", GridData.ItemID);
							JsonWriter->WriteValue<int>("Num", GridData.Num);
							JsonWriter->WriteObjectEnd();
						}
						JsonWriter->WriteArrayEnd();
						
						JsonWriter->WriteObjectEnd();
					}
					
				}
				JsonWriter->WriteArrayEnd();

				// PlayerData.InventoryData.StorageGridDatas
				JsonWriter->WriteIdentifierPrefix("StorageGridDatas");
				JsonWriter->WriteArrayStart();
				{
					for (auto KeyValuePair : GameSaveData.PlayerData.InventoryData.StorageGridDatas)
					{
						JsonWriter->WriteObjectStart();

						JsonWriter->WriteValue<int>("ItemClassificationEnumValue", KeyValuePair.Key);

						JsonWriter->WriteIdentifierPrefix("ClassifiedStorageGridData");
						JsonWriter->WriteArrayStart();
						for (auto GridData : KeyValuePair.Value.ClassifiedStorageGridDataArray)
						{
							JsonWriter->WriteObjectStart();
							JsonWriter->WriteValue<int>("ID", GridData.ItemID);
							JsonWriter->WriteValue<int>("Num", GridData.Num);
							JsonWriter->WriteObjectEnd();
						}
						JsonWriter->WriteArrayEnd();

						JsonWriter->WriteObjectEnd();
					}
				}
				JsonWriter->WriteArrayEnd();
			}
			JsonWriter->WriteObjectEnd();
		}
		JsonWriter->WriteObjectEnd();


		
		// ItemOnGroundData
		JsonWriter->WriteIdentifierPrefix("ItemOnGroundData");
		JsonWriter->WriteArrayStart();
		{
			for (auto KeyValuePair : GameSaveData.ItemOnGroundData)
			{
				JsonWriter->WriteObjectStart();

				JsonWriter->WriteValue<FString>("Index", KeyValuePair.Key.ToString());
				
				JsonWriter->WriteIdentifierPrefix("Location");
				JsonWriter->WriteArrayStart();
				JsonWriter->WriteValue<float>(KeyValuePair.Value.Location.X);
				JsonWriter->WriteValue<float>(KeyValuePair.Value.Location.Y);
				JsonWriter->WriteValue<float>(KeyValuePair.Value.Location.Z);
				JsonWriter->WriteArrayEnd();

				JsonWriter->WriteValue<int>("ID", KeyValuePair.Value.ID);
				JsonWriter->WriteValue<int>("Num", KeyValuePair.Value.Num);
				
				JsonWriter->WriteObjectEnd();
			}
		}
		JsonWriter->WriteArrayEnd();

		
	}
	JsonWriter->WriteObjectEnd();
	JsonWriter->Close();
	
	return JsonStr;
}

FGridData FGameSaveTool::GetClassifiedGridDataByIndex(TEnumAsByte<EItemClassification> Classification, int Index)
{
	auto GameSaveData = FFileTool::LoadGame();
	if (GameSaveData.PlayerData.InventoryData.GridDatas.Find(Classification)->ClassifiedGridDataArray.IsValidIndex(Index))
	{
		return GameSaveData.PlayerData.InventoryData.GridDatas.Find(Classification)->ClassifiedGridDataArray[Index];
	}
	return FGridData(0, 0);
}

int FGameSaveTool::GetTotalItemNumberByClassification(TEnumAsByte<EItemClassification> Classification)
{
	auto GameSaveData = FFileTool::LoadGame();
	return GameSaveData.PlayerData.InventoryData.GridDatas.Find(Classification)->ClassifiedGridDataArray.Num();
}

void FGameSaveTool::SaveGrid(int Index, FGridData GridData)
{
	auto GameSaveData = FFileTool::LoadGame();
	if (Index == -1)
	{
		GameSaveData.PlayerData.InventoryData.GridDatas.Find(TEnumAsByte<EItemClassification>(GridData.ItemID / 10000 - 1))->ClassifiedGridDataArray.Add(GridData);
	}
	else
	{
		GameSaveData.PlayerData.InventoryData.GridDatas.Find(TEnumAsByte<EItemClassification>(GridData.ItemID / 10000 - 1))->ClassifiedGridDataArray[Index] = GridData;
	}
	FFileTool::SaveGame(GameSaveData);
}

void FGameSaveTool::SaveStorageGrid(int Index, FGridData GridData)
{
	auto GameSaveData = FFileTool::LoadGame();
	if (Index == -1)
	{
		GameSaveData.PlayerData.InventoryData.StorageGridDatas.Find(TEnumAsByte<EItemClassification>(GridData.ItemID / 10000 - 1))->ClassifiedStorageGridDataArray.Add(GridData);
	}
	else
	{
		GameSaveData.PlayerData.InventoryData.StorageGridDatas.Find(TEnumAsByte<EItemClassification>(GridData.ItemID / 10000 - 1))->ClassifiedStorageGridDataArray[Index] = GridData;
	}
	FFileTool::SaveGame(GameSaveData);
}

TMap<FName, FItemOnGroundData> FGameSaveTool::GetItemOnGroundDatas()
{
	auto GameSaveData = FFileTool::LoadGame();
	return GameSaveData.ItemOnGroundData;
}

FItemOnGroundData FGameSaveTool::GetItemOnGroundDataByIndex(FName Index)
{
	auto GameSaveData = FFileTool::LoadGame();
	return *GameSaveData.ItemOnGroundData.Find(Index);
}

void FGameSaveTool::SetItemOnGroundDataByIndex(FName Index, FItemOnGroundData NewData)
{
	auto GameSaveData = FFileTool::LoadGame();
	*GameSaveData.ItemOnGroundData.Find(Index) = NewData;

	FFileTool::SaveGame(GameSaveData);
}

void FGameSaveTool::RemoveItemOnGroundDataByIndex(const FName &Index)
{
	auto GameSaveData = FFileTool::LoadGame();
	GameSaveData.ItemOnGroundData.Remove(Index);
	FFileTool::SaveGame(GameSaveData);
}

bool FGameSaveTool::ItemOnGroundExist(FName Index)
{
	FItemOnGroundData *ItemOnGroundData = FFileTool::LoadGame().ItemOnGroundData.Find(Index);
	return !!ItemOnGroundData;
}

void FGameSaveTool::AddItemOnGroundData(FName Index, FItemOnGroundData NewData)
{
	auto ItemOnGroundDatas = FGameSaveTool::GetItemOnGroundDatas();
	int NumTemp = 0;
	
	do
	{
		Index = FName(FString("Item_") + FString::FromInt(NumTemp));
		++NumTemp;
	} while (ItemOnGroundDatas.Contains(Index));
	NewData.ItemOnGroundIndex = Index;
	auto GameSaveData = FFileTool::LoadGame();
	GameSaveData.ItemOnGroundData.Add(Index, NewData);
	FFileTool::SaveGame(GameSaveData);
}
