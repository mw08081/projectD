// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ProjectDPlayerController.generated.h"



/**
 * 
 */
UCLASS()
class PROJECTD_API AProjectDPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AProjectDPlayerController();
protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> WB_IngameOption_class;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UIngameHUD> WB_Ingame_class;

	class UUserWidget* WB_IngameOption;
	class UIngameHUD* WB_IngameHUD;

public:
	UFUNCTION(BlueprintCallable)
	void ManageIngameOption();

	UFUNCTION(BlueprintCallable)
	bool UpdatePlayerAttackMode(bool IsSwing);

	UFUNCTION(BlueprintCallable)
	void UpdatePBElapsedChargeTime(float Value);

	UFUNCTION(BlueprintCallable)
	void UpdatePBBlowCount(float Value);

	/*UFUNCTION()
	void HandlePlayerStateChanged(int32 State);*/

};
