// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveInter.h"
#include "GameFramework/Actor.h"
#include "ItemOnGround.generated.h"

class USphereComponent;
UCLASS()
class DS3_INVENTORY_API AItemOnGround : public AActor, public IInteractiveInter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemOnGround();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	FName ItemIndex;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UParticleSystemComponent *ParticleSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent *SphereCollision;

public:
	// todo : finish ItemOnGround
	UFUNCTION()
	void OnUpdateItemOnGround(FName Index);

	UFUNCTION()
	void Init(FName Index);

	void UpdataDisplay(FName Index);
	
	// interactive interface impl
	virtual void Enter(AActor *User) override;
	virtual void StayTick(AActor *User, float DeltaTime) override;
	virtual void Exit(AActor *User) override;

	virtual void BeginInteraction(AActor *User, UInteractiveComp *InteractiveComponent) override;
	virtual void InteractionTick(AActor *User, float DeltaTime, UInteractiveComp *InteractiveComponent) override;
	virtual void EndInteraction(AActor *User) override;
	
};
