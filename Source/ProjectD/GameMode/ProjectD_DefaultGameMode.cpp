// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/WorldSettings.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

#include "EngineUtils.h"

#include "Component/LvObjectRoot.h"
#include "System/ObjectPoolSystem.h"
#include "GameMode/ProjectD_DefaultGameMode.h"


AProjectD_DefaultGameMode::AProjectD_DefaultGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AProjectD_DefaultGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	CalcAllObjectPriceInWorld();

	GetWorldTimerManager().SetTimer(FadeInHandle, this, &AProjectD_DefaultGameMode::SetCanFadeIn, 2.f, false);
	InitObjectPool_NsDisplay();
}
void AProjectD_DefaultGameMode::SetCanFadeIn()
{
	bCanFadeIn = true;
}

void AProjectD_DefaultGameMode::Tick(float deltaTime)
{
	ElapsedGameTime += deltaTime;
	FadeIn(deltaTime);
}
void AProjectD_DefaultGameMode::FadeIn(float dt)
{
	if (bCanFadeIn && FadeInValue < 1) {
		FadeInValue += dt;
		//UE_LOG(LogTemp, Display, TEXT("%f"), FadeInValue);
	}

	if (FadeInValue > 1) {
		UE_LOG(LogTemp, Display, TEXT("SLOW!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"));
		GetWorld()->GetWorldSettings()->SetTimeDilation(SLOW_TIMEDILATION);

		bCanFadeIn = false;
		FadeInValue = 0;
	}
}

void AProjectD_DefaultGameMode::CalcAllObjectPriceInWorld()
{
	for (const AActor* ActorPtr : FActorRange(GetWorld()))
	{
		ULvObjectRoot* lvObjectRoot = ActorPtr->FindComponentByClass<ULvObjectRoot>();
		if (lvObjectRoot != nullptr) {
			UE_LOG(LogTemp, Display, TEXT("%s 's price : %d"), *(ActorPtr->GetActorNameOrLabel()), lvObjectRoot->objectPrice);

			TotalObjectPrice += lvObjectRoot->objectPrice;
		} 
	}

	Phase1_ClearPrice = TotalObjectPrice * PHASE1_CLEAR_PERCENTAGE;
	Phase2_ClearPrice = TotalObjectPrice * PHASE2_CLEAR_PERCENTAGE;
	UE_LOG(LogTemp, Display, TEXT("phase 1 : %d , phase 2: %d"), Phase1_ClearPrice, Phase2_ClearPrice);
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
