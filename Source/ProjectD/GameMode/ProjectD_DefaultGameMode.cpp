// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/ProjectD_DefaultGameMode.h"
#include "System/ObjectPoolSystem.h"
#include "TimerManager.h"

AProjectD_DefaultGameMode::AProjectD_DefaultGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AProjectD_DefaultGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(FadeInHandle, this, &AProjectD_DefaultGameMode::SetCanFadeIn, 2.f, false);
	InitObjectPool_NsDisplay();
}
void AProjectD_DefaultGameMode::SetCanFadeIn()
{
	bCanFadeIn = true;
}

void AProjectD_DefaultGameMode::Tick(float deltaTime)
{
	//ElapsedGameTime += deltaTime;
	FadeIn(deltaTime);
}
void AProjectD_DefaultGameMode::FadeIn(float dt)
{
	if (bCanFadeIn && FadeInValue < 1) {
		FadeInValue += dt;
		UE_LOG(LogTemp, Display, TEXT("%f"), FadeInValue);
	}
}


void AProjectD_DefaultGameMode::InitObjectPool_NsDisplay()
{
	ObjectPoolSystem_NsDisplay = GetWorld()->SpawnActor<AObjectPoolSystem>();
	ObjectPoolSystem_NsDisplay->InitializePool_NsDisplay(PoolTargetClass_NsDisplay, PoolSize_NsDisplay);
}

ANsDisplay* AProjectD_DefaultGameMode::Get_NsDisplay()
{
	ANsDisplay* obj = ObjectPoolSystem_NsDisplay->GetPooledObject_NsDisplay();
	return obj;
}

void AProjectD_DefaultGameMode::Return_NsDisplay(ANsDisplay* _NsDisplay)
{

}
