// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/NsDisplay.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

#include "GameMode/ProjectD_DefaultGameMode.h"
#include "System/ObjectPoolSubsystem.h"


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

void ANsDisplay::SetNs(UNiagaraSystem* ns, FVector Location)
{
	nsComponent->SetAsset(ns);
	nsComponent->Activate();

	SetActorLocation(Location);

	SetIsActive(true);
}

void ANsDisplay::ReturnToObjectPoolSubsystem()
{
	UObjectPoolSubsystem* ObjectPoolSubsystem = GetWorld()->GetSubsystem<UObjectPoolSubsystem>();
	if (ObjectPoolSubsystem == nullptr) return;

	ObjectPoolSubsystem->ReturnObjectToPool(this);
}

void ANsDisplay::CheckReturnCondition(float dt)
{
	elapsedPlayTime += dt;

	// 1. fade out 
	if (elapsedPlayTime > MAX_PLAY_TIME) {
		nsComponent->Deactivate();
	}

	// 2. return
	if (elapsedPlayTime > MAX_RESIDUAL_TIME) {
		ReturnToObjectPoolSubsystem();
	}
}

void ANsDisplay::Activate()
{
	SetActorHiddenInGame(false);
}

void ANsDisplay::Deactivate()
{
	SetActorHiddenInGame(true);

	nsComponent->Deactivate();
	elapsedPlayTime = 0;
}

void ANsDisplay::SetIsActive(bool _bIsActive)
{
	bIsActive = _bIsActive;
}

bool ANsDisplay::GetIsActive()
{
	return bIsActive;
}

