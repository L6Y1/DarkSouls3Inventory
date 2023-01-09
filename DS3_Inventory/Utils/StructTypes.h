// Fill out your copyright notice in the Description page of Project Settings.

// ReSharper disable CppPossiblyUninitializedMember
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "StructTypes.generated.h"

/**
 * 
 */
UCLASS()
class DS3_INVENTORY_API UStructTypes : public UObject
{
	GENERATED_BODY()
	
};

////-------------------------------- REGION --------------------------------////
#pragma region Enums

/*UENUM(BlueprintType)
enum ETestEnum { Test1, ENUM_st = Test1, Test2, Test3 };

USTRUCT(BlueprintType)
struct FTestStruct : public FTableRowBase
{
	GENERATED_BODY()

public:
	FTestStruct() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ETestEnum> Test;
};*/

// 物品分类
UENUM(BlueprintType)
enum EItemClassification { Consumables, ENUM_START = Consumables,
	 Weapon, WearableEquipment, Important, Magics, Rings, ENUM_END };

// 属性加成
UENUM(BlueprintType)
enum EStatBonuses { NONE, E, D, C, B, A, S };

// 物理伤害种类 Standard 标准， Slash 斩击， Thrust 突刺， Strike 打击
UENUM(BlueprintType)
enum EPhysicalDamageType { Standard, Slash, Thrust, Strike };

// 攻击力种类
UENUM(BlueprintType)
enum EAttackType { Physical, Magic, Fire, Lightning, Dark };

// 特殊效果
UENUM()
enum EAuxEffects { BleedEffect, PoisonDamage, FrostEffect, CurseEffect};

// 玩家属性
UENUM(BlueprintType)
enum EPlayerStats { Vigor, Attunement, Endurance, Vitality, Strength, Dexterity, Intelligence, Faith, Luck };

#pragma endregion Enums
////-------------------------------- END_REGION --------------------------------////




////-------------------------------- REGION --------------------------------////
#pragma region Item_AttrStructs
// BASE class of item in inventory
USTRUCT(BlueprintType)
struct FInventoryItemAttr : public FTableRowBase
{
	GENERATED_BODY()

public:
	FInventoryItemAttr() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemImage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TEnumAsByte<EItemClassification> ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxStackNum;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShowNum;
};

// Consumables
USTRUCT(BlueprintType)
struct FConsumablesItemAttr : public FInventoryItemAttr
{
	GENERATED_BODY()

public:
	FConsumablesItemAttr() { ItemType = EItemClassification::Consumables; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxStorageNum;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TEnumAsByte<EPlayerStats>, TEnumAsByte<EStatBonuses>> StatBonuses;
};

// Weapons
USTRUCT()
struct FWeaponItemAttr : public FInventoryItemAttr
{
	GENERATED_BODY()

public:
	FWeaponItemAttr() {	ItemType = EItemClassification::Weapon; }

	/* common attr for weapon */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FName Upgrades = "NONE";
	
	// straight sword, spear... etc.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName WeaponClassification;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TEnumAsByte<EPhysicalDamageType>> PhysicalDamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Skill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SkillFPCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxDurability;

	/* attack value */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TEnumAsByte<EAttackType>, int> Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Critical;

	/* damage reduction value */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TEnumAsByte<EAttackType>, float> Reduction;
	// determines the amount of stamina expended to block an incoming attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Stability;

	/* special effect */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TEnumAsByte<EAuxEffects>, int> AuxEffects;

	/* stat bonuses */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TEnumAsByte<EPlayerStats>, TEnumAsByte<EStatBonuses>> StatBonuses;

	/* stats needed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TEnumAsByte<EPlayerStats>, int> StatsNeeded;
	
};

// Wearable equipments, armour,helmet etc.
USTRUCT(BlueprintType)
struct FWearableEquipmentItemAttr : public FInventoryItemAttr
{
	GENERATED_BODY()

public:
	FWearableEquipmentItemAttr() {	ItemType = EItemClassification::WearableEquipment; }
	
	/* common attr */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxDurability;

	/* damage reduction */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TEnumAsByte<EAttackType>, float> Reduction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TEnumAsByte<EPhysicalDamageType>, float> PhysicalReduction;

	/* AuxEffect resistant */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TEnumAsByte<EAuxEffects>, int> Resistant;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Poise;
};

// important items
USTRUCT(BlueprintType)
struct FImportantItemAttr : public FInventoryItemAttr
{
	GENERATED_BODY()

public:
	FImportantItemAttr() {	ItemType = EItemClassification::Important; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemEffect;
};

// Magics
USTRUCT(BlueprintType)
struct FMagicItemAttr : public FInventoryItemAttr
{
	GENERATED_BODY()
	
public:
	FMagicItemAttr() {	ItemType = EItemClassification::Magics; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MagicType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxStorageNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int FPCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MemoryBlockUsage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TEnumAsByte<EPlayerStats>, int> StatsNeeded;
};

// Rings 
USTRUCT(BlueprintType)
struct FRingItemAttr : public FInventoryItemAttr
{
	GENERATED_BODY()
	
public:
	FRingItemAttr() { ItemType = EItemClassification::Rings; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemEffect;
};

#pragma endregion Item_AttrStructs
////-------------------------------- END_REGION --------------------------------////




////-------------------------------- REGION --------------------------------////
#pragma region GameSave_DataStructs

USTRUCT(BlueprintType)
struct FGridData
{
	GENERATED_BODY()

public:
	FGridData() {}
	
	FGridData(int ID, int Num): ItemID(ID), Num(Num) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Num;

};


USTRUCT(BlueprintType)
struct FClassifiedGridData
{
	GENERATED_BODY()

public:
	FClassifiedGridData() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FGridData> ClassifiedGridDataArray;
};

USTRUCT(BlueprintType)
struct FClassifiedStorageGridData
{
	GENERATED_BODY()

public:
	FClassifiedStorageGridData() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FGridData> ClassifiedStorageGridDataArray;
};

USTRUCT(BlueprintType)
struct FInventoryData
{
	GENERATED_BODY()

public:
	FInventoryData() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TEnumAsByte<EItemClassification>, FClassifiedGridData> GridDatas;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TEnumAsByte<EItemClassification>, FClassifiedStorageGridData> StorageGridDatas;
};



USTRUCT(BlueprintType)
struct FPlayerStats
{
	GENERATED_BODY()

public:
	FPlayerStats() {}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Curse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxFP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentFP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TEnumAsByte<EPlayerStats>, int> Stats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxEquipLoad;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Poise;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ItemDiscovery;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AttunementSlots;
};


USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()

public:
	FPlayerData() {}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPlayerStats PlayerStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInventoryData InventoryData;

};


USTRUCT(BlueprintType)
struct FItemOnGroundData
{
	GENERATED_BODY()

public:
	FItemOnGroundData() {}

	FItemOnGroundData(FName Index, FVector Location, int ID, int Num)
	: ItemOnGroundIndex(Index),Location(Location), ID(ID), Num(Num)  {}
	
	// unique id(FName) to identify the item on ground
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemOnGroundIndex;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Num;
};

USTRUCT(BlueprintType)
struct FGameSaveData
{
	GENERATED_BODY()

public:
	FGameSaveData() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPlayerData PlayerData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, FItemOnGroundData> ItemOnGroundData;
	
};
#pragma endregion GameSave_DataStructs
////-------------------------------- END_REGION --------------------------------////




////-------------------------------- REGION --------------------------------////
#pragma region Menu_AttrStructs

USTRUCT(BlueprintType)
struct FStatusType1Attr : public FTableRowBase
{
	GENERATED_BODY()

public:
	FStatusType1Attr() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName StatusBaseImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, FName> StatsImages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName StatusUnitClass;
	
};


USTRUCT(BlueprintType)
struct FItemGridType1Attr : public FTableRowBase
{
	GENERATED_BODY()

public:
	FItemGridType1Attr() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D GridSize;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName GridBaseImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D DishImageSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName DishImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D ItemImageSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SelectImage;
};

USTRUCT(BlueprintType)
struct FSortCardsType1Attr : public FTableRowBase
{
	GENERATED_BODY()

public:
	FSortCardsType1Attr() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D SortCardsSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D CardContainerSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName LeftButtonImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName RightButtonImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SortCardType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SortCardNum = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TEnumAsByte<EItemClassification>, FName> CardImage;
};


USTRUCT(BlueprintType)
struct FInventoryType1Attr : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	FInventoryType1Attr() {}

	// size of the full inventory widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D InventorySize;

	// size of the inventory item background image
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D InventoryBaseImageSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName InventoryBaseImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SortCardWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemGridWidgetClass;
};


USTRUCT(BlueprintType)
struct FNavButtonAttr : public FTableRowBase
{
	GENERATED_BODY()

public:
	FNavButtonAttr() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ButtonLayoutStyle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D ButtonSize;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ButtonImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName HoveredImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ToggledFullScreenWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> ToggledFullScreenWidgetPartsClass;
	
	
	
};


USTRUCT(BlueprintType)
struct FMenuTopType1Attr : public FTableRowBase
{
	GENERATED_BODY()

public:
	FMenuTopType1Attr() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D WidgetSize;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MenuTopBackGroundImg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MenuSelectImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemSelectImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NavButtonType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName QuickBarType;

	
};

USTRUCT(BlueprintType)
struct FFullScreenDisplayType1Attr : public FTableRowBase
{
	GENERATED_BODY()

public:
	FFullScreenDisplayType1Attr() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TitleBGImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D TitleImageSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TitleImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TitleText;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName FooterBGImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MenuBaseImage;
};

#pragma endregion Menu_AttrStructs
////-------------------------------- END_REGION --------------------------------////