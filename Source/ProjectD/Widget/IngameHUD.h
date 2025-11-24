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

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Score;
	void UpdateScore(int32 Value);
	
	UPROPERTY(meta = (BindWidget))
	class UImage* Img_PlayerAttackMode;

	UPROPERTY(EditDefaultsOnly, Category = "IMG|AttackMode")
	class UTexture2D* Img_PunchMode;
	UPROPERTY(EditDefaultsOnly, Category = "IMG|AttackMode")
	class UTexture2D* Img_SwingMode;
	
	FSlateBrush Brush;
	void UpdatePlayerAttackMode(bool IsSwing);

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_BlowCount;
	void UpdateBlowCount(float Value);

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_ElapsedChargeTime;
	void UpdateElpasedChargeTime(float Value);
};
