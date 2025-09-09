// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/ProjectDPlayerController.h"

#include "Kismet/GameplayStatics.h"

#include "Blueprint/UserWidget.h"

#include "Widget/IngameHUD.h"



AProjectDPlayerController::AProjectDPlayerController()
{
}

void AProjectDPlayerController::BeginPlay()
{
	if (IsValid(WB_Ingame_class))
	{
		WB_IngameHUD = CreateWidget<UIngameHUD>(this, WB_Ingame_class);
		if (IsValid(WB_IngameHUD))
		{
			WB_IngameHUD->AddToViewport();
		}
	}

	if (IsValid(WB_IngameOption_class))
	{
		WB_IngameOption = CreateWidget<UUserWidget>(this, WB_IngameOption_class);
	}
}

void AProjectDPlayerController::ManageIngameOption()
{
	if (IsValid(WB_IngameOption))
	{
		bool bIsOn = !WB_IngameOption->IsInViewport();
		
		// 게임 정지
		UGameplayStatics::SetGamePaused(GetWorld(), bIsOn);
		
		// 마우스 커서
		SetShowMouseCursor(bIsOn);

		// 분기명령어
		if (bIsOn)
		{
			// 인풋모드
			SetInputMode(FInputModeGameAndUI());
			// WB Show
			WB_IngameOption->AddToViewport();
		}
		else
		{
			SetInputMode(FInputModeGameOnly());
			WB_IngameOption->RemoveFromParent();
		}
	}
}

bool AProjectDPlayerController::UpdatePlayerAttackMode(bool IsSwing)
{
	if (IsValid(WB_IngameHUD))
	{
		WB_IngameHUD->UpdatePlayerAttackMode(IsSwing);
	}
	return IsSwing;
}

void AProjectDPlayerController::UpdatePBElapsedChargeTime(float Value)
{
	if (IsValid(WB_IngameHUD))
	{
		WB_IngameHUD->UpdateElpasedChargeTime(Value);
	}
}

void AProjectDPlayerController::UpdatePBBlowCount(float Value)
{
	if(IsValid(WB_IngameHUD))
	{
		WB_IngameHUD->UpdateBlowCount(Value);
	}
}

void AProjectDPlayerController::UpdateTxtScore(int32 Value)
{
	if (IsValid(WB_IngameHUD))
	{
		WB_IngameHUD->UpdateScore(Value);
	}
}
