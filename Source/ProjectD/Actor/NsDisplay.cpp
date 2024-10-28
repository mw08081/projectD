// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/NsDisplay.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "GameMode/ProjectD_DefaultGameMode.h"
#include "System/ObjectPoolSystem.h"

// Sets default values
ANsDisplay::ANsDisplay()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	nsComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara System"));
	RootComponent = nsComponent;
}

// Called when the game starts or when spawned
void ANsDisplay::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANsDisplay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bIsActive) {
		CheckReturnCondition(DeltaTime);
	}
}

void ANsDisplay::SetNs(UNiagaraSystem* ns)
{
	nsComponent->SetAsset(ns);
	nsComponent->Activate();

	SetIsActive(true);
}

/// <summary>
/// Niagara System 비활성화
/// </summary>
void ANsDisplay::InitNs()
{
	nsComponent->Deactivate();
	//elapsedPlayTime = 0;
}

void ANsDisplay::CheckReturnCondition(float dt)
{
	elapsedPlayTime += dt;
	if (elapsedPlayTime > MAX_PLAY_TIME) {
		InitNs();
	}

	if (elapsedPlayTime > MAX_RESIDUAL_TIME) {
		AProjectD_DefaultGameMode* gameMode = Cast<AProjectD_DefaultGameMode>(GetWorld()->GetAuthGameMode());
		if (gameMode) {
			gameMode->ObjectPoolSystem_NsDisplay->ReturnPooledObject_NsDisplay(this);
			elapsedPlayTime = 0.f;
		}
	}
}

void ANsDisplay::SetIsActive(bool _bIsActive)
{
	bIsActive = _bIsActive;
}

bool ANsDisplay::GetIsActive()
{
	return bIsActive;
}

