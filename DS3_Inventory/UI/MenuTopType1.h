// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DS3_Inventory/Utils/StructTypes.h"
#include "DS3_Inventory/Utils/UIManager/UIState.h"
#include "MenuTopType1.generated.h"

class UHorizontalBox;
class UTextBlock;
class UImage;
class UBorder;
class USizeBox;
/**
 * 
 */
UCLASS()
class DS3_INVENTORY_API UMenuTopType1 : public UUIState
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual void ReceiveEnterState_Implementation(EStackAction StackAction) override;
	virtual void ReceiveExitState_Implementation(EStackAction StackAction) override;
public:
	// widgets
	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	USizeBox *MenuTopSizeBox;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UBorder *MenuTopBGBorder;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UImage *MenuSelectImage;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UImage *ItemSelectImage;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UTextBlock *MenuSelectText;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UTextBlock *ItemSelectText;

	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UHorizontalBox *MenuHorBox;
	
	UPROPERTY(meta=(BindWidget), VisibleAnywhere, BlueprintReadOnly)
	UNamedSlot *QuickBarSlot;
	
public:
	

	UFUNCTION()
	void Init(FMenuTopType1Attr MenuTopType1Attr);

	UFUNCTION()
	void UpdateHint(FName Name, bool bShouldShow, bool bIsMenu);
};
