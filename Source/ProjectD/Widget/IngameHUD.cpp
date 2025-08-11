// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/IngameHUD.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UIngameHUD::UpdatePBBlowCount(float Value)
{
	PB_BlowCount->SetPercent(Value);
}

void UIngameHUD::UpdatePBElpasedChargeTime(float Value)
{
	PB_ElapsedChargeTime->SetPercent(Value);
}
