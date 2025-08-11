// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IngameHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UIngameHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_DestoryedAmount;
	
	UPROPERTY(meta = (BindWidget))
	class UImage* Img_PlayerAttackMode;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_BlowCount;
	void UpdatePBBlowCount(float Value);

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_ElapsedChargeTime;
	void UpdatePBElpasedChargeTime(float Value);

};
