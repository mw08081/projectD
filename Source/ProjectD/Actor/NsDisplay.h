// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NsDisplay.generated.h"

UCLASS()
class PROJECTD_API ANsDisplay : public AActor
{
	GENERATED_BODY()
	
public:	
	ANsDisplay();

protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;

//components
private:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* nsComponent;

//code Variable
public:
private:
	bool bIsActive;
	float elapsedPlayTime;
	const float MAX_PLAY_TIME = 1.5f;
	const float MAX_RESIDUAL_TIME = 5.f;	//최대 잔류 시간(너무 빨리 돌아가면 NS 위치버그발생..)

public:
	UFUNCTION(BlueprintCallable)
	void SetNs(class UNiagaraSystem* ns);
	void InitNs();
	void CheckReturnCondition(float dt);

	void SetIsActive(bool _bIsActive);
	bool GetIsActive();
};
