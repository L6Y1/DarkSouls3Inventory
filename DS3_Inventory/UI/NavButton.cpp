// Fill out your copyright notice in the Description page of Project Settings.


#include "NavButton.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"

void UNavButton::NativeConstruct()
{
	Super::NativeConstruct();
	
	HoveredImage->SetVisibility(ESlateVisibility::Collapsed);
	
	NavButtonSizeBox->SetWidthOverride(93);
	NavButtonSizeBox->SetHeightOverride(93);

	NavButton->OnHovered.AddDynamic(this, &UNavButton::ToggleHoveredPic);
	NavButton->OnUnhovered.AddDynamic(this, &UNavButton::ToggleHoveredPic);

}

void UNavButton::ToggleHoveredPic()
{
	HoveredImage->IsVisible() ?
		HoveredImage->SetVisibility(ESlateVisibility::Collapsed) :
		HoveredImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UNavButton::Init()
{
	// TODO : init the NavButton here
}


