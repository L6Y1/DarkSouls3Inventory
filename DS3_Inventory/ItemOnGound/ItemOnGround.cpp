// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemOnGround.h"

#include "InteractiveComp.h"
#include "Blueprint/UserWidget.h"
#include "Components/SphereComponent.h"
#include "DS3_Inventory/GameMode/DS3_InventoryPC.h"
#include "DS3_Inventory/Utils/DataAssetMananger/DataAssetMananger.h"
#include "DS3_Inventory/Utils/DataTableTool/DataTableTool.h"
#include "DS3_Inventory/Utils/FileTool/FileTool.h"
#include "DS3_Inventory/Utils/GlobalEventManager/GlobalEventManager.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AItemOnGround::AItemOnGround()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	RootComponent = SphereCollision;
	SphereCollision->SetSimulatePhysics(true);
	SphereCollision->SetNotifyRigidBodyCollision(true);
	SphereCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	SphereCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	SphereCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	FBodyInstance *RootBI = SphereCollision->GetBodyInstance(NAME_None, false);;
	RootBI->bLockXRotation = true;
	RootBI->bLockYRotation = true;
	RootBI->bLockZRotation = false;
	
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	ParticleSystem->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AItemOnGround::BeginPlay()
{
	Super::BeginPlay();
	FGlobalEventManager::RegisterEvent(FName("UpdateItemOnGroundEvent"), this, FName("OnUpdateItemOnGround"));
}

void AItemOnGround::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	FGlobalEventManager::UnRegisterEvent(FName("UpdateItemOnGroundEvent"), this);
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AItemOnGround::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemOnGround::OnUpdateItemOnGround(FName Index)
{
	if (this->ItemIndex != Index)
		return;
	if (FGameSaveTool::ItemOnGroundExist(Index))
	{
		// leave blank here
		
	}
	else
	{
		this->Destroy();
	}
}

void AItemOnGround::Init(FName Index)
{
	this->ItemIndex = Index;
	UpdataDisplay(Index);
}

void AItemOnGround::UpdataDisplay(FName Index)
{
	// leave blank
}





void AItemOnGround::Enter(AActor *User)
{
	auto *Controller = Cast<APawn>(User)->Controller;
	auto ItemOnGroundData = FGameSaveTool::GetItemOnGroundDataByIndex(ItemIndex);

	
	if (IsValid(Controller) && Controller->IsPlayerController())
	{
		auto ItemOnGroundAttr = FDataTableTool::GetItemOnGroundAttr(IntToName(ItemOnGroundData.ID));
        ADataAssetMananger::RequestAsyncLoadClass(this, ItemOnGroundAttr->TipWidgetClass, [this](UClass *AssetClass)
        {
        	FGlobalEventManager::TriggerEvent(FName("ToggleTipEvent"), &AssetClass);
        });
	}
	
}

void AItemOnGround::StayTick(AActor *User, float DeltaTime)
{
}

void AItemOnGround::Exit(AActor *User)
{
	FGlobalEventManager::TriggerEvent(FName("ToggleTipEvent"), this->StaticClass());
}

void AItemOnGround::BeginInteraction(AActor *User, UInteractiveComp *InteractiveComponent)
{
	auto ItemOnGroundData = FGameSaveTool::GetItemOnGroundDataByIndex(ItemIndex);
	auto ItemOnGroundAttr = FDataTableTool::GetItemOnGroundAttr(IntToName(ItemOnGroundData.ID));
	ADataAssetMananger::RequestAsyncLoadClass(this, ItemOnGroundAttr->PickupWidgetClass, [ItemOnGroundData, this](UClass *AssetClass)
	{
		struct
		{
			FItemOnGroundData ItemOnGroundData;
			UClass *Class;
		} Params;
		Params.Class = AssetClass;
		Params.ItemOnGroundData = ItemOnGroundData;
		FGlobalEventManager::TriggerEvent(FName("TogglePickupEvent"), &Params);
	});

}

void AItemOnGround::InteractionTick(AActor *User, float DeltaTime, UInteractiveComp *InteractiveComponent)
{
	InteractiveComponent->EndInteraction(User);
}

void AItemOnGround::EndInteraction(AActor *User)
{
	struct
	{
		AActor *User;
		FName ItemIndex;
	} Params;
	Params.ItemIndex = ItemIndex;
	Params.User = User;
	FGlobalEventManager::TriggerEvent(FName("StartPickupItemEvent"), &Params);
	
	this->Destroy();
}

