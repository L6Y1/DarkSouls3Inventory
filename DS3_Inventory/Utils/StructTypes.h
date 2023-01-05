// Fill out your copyright notice in the Description page of Project Settings.

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

////-------------------------------- region --------------------------------////
#pragma region Enums
// 物品分类
UENUM(BlueprintType)
enum EItemClassification { ENUM_START, Consumables = ENUM_START,
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


////-------------------------------- region --------------------------------////
#pragma region ItemAttrs
// BASE class of item in inventory
USTRUCT(BlueprintType)
struct FInventoryItemAttr : public FTableRowBase
{
	GENERATED_BODY()

public:
	// ReSharper disable once CppPossiblyUninitializedMember
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
	// ReSharper disable once CppPossiblyUninitializedMember
	FConsumablesItemAttr() {}

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
	// ReSharper disable once CppPossiblyUninitializedMember
	FWeaponItemAttr() {}

	/* common attr for weapon */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FName Upgrades;
	
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
	// ReSharper disable once CppPossiblyUninitializedMember
	FWearableEquipmentItemAttr() {}
	
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
	FImportantItemAttr() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemEffect;
};

// Magics
USTRUCT(BlueprintType)
struct FMagicItemAttr
{
	GENERATED_BODY()
	
public:
	// ReSharper disable once CppPossiblyUninitializedMember
	FMagicItemAttr() {}

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
struct FRingItemAttr
{
	GENERATED_BODY()
	
public:
	// ReSharper disable once CppPossiblyUninitializedMember
	FRingItemAttr() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemEffect;
};

#pragma endregion ItemAttrs



////-------------------------------- region --------------------------------////
#pragma region MenuAttrs
USTRUCT(BlueprintType)
struct FItemGridType1Attr
{
	GENERATED_BODY()

public:
	FItemGridType1Attr() {}

	
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

#pragma endregion MenuAttrs