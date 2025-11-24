// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/IngameHUD.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Styling/SlateBrush.h"



void UIngameHUD::NativeConstruct()
{
	if (IsValid(Img_PlayerAttackMode))
	{
		Brush.SetResourceObject(Img_PunchMode);
		Img_PlayerAttackMode->SetBrush(Brush);
	}


	if (IsValid(PB_BlowCount))
	{
		PB_BlowCount->SetPercent(0);
	}

	if (IsValid(PB_ElapsedChargeTime))
	{
		PB_ElapsedChargeTime->SetPercent(0);
	}
}

void UIngameHUD::UpdateScore(int32 Value)
{
	FString Cont = FString::FromInt(Value);
	Txt_Score->SetText(FText::FromString(Cont));
}

void UIngameHUD::UpdatePlayerAttackMode(bool IsSwing)
{
	if (IsValid(Img_PlayerAttackMode))
	{
		Brush.SetResourceObject((IsSwing) ? (Img_SwingMode) : (Img_PunchMode));

		Img_PlayerAttackMode->SetBrush(Brush);
	}
}

void UIngameHUD::UpdateBlowCount(float Value)
{
	if (IsValid(PB_BlowCount))
	{
		PB_BlowCount->SetPercent(Value);
	}
	
}

void UIngameHUD::UpdateElpasedChargeTime(float Value)
{
	if (IsValid(PB_ElapsedChargeTime))
	{
		PB_ElapsedChargeTime->SetPercent(Value);
	}
}
