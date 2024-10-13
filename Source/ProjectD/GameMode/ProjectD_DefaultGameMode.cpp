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

	if(GetWorld()->GetTimerManager().GetTimerElapsed(RollbackTimedilationHandle) != -1)
		UE_LOG(LogTemp, Display, TEXT("RollbackTimedilationHandle : %f"), GetWorld()->GetTimerManager().GetTimerElapsed(RollbackTimedilationHandle));
	if (GetWorld()->GetTimerManager().GetTimerElapsed(CoolDownSlowHandle) != -1)
		UE_LOG(LogTemp, Display, TEXT("CoolDownSlowHandle : %f"), GetWorld()->GetTimerManager().GetTimerElapsed(CoolDownSlowHandle));

}
void AProjectD_DefaultGameMode::FadeIn(float dt)
{
	if (bCanFadeIn && FadeInValue < 1) {
		FadeInValue += dt;
		//UE_LOG(LogTemp, Display, TEXT("%f"), FadeInValue);
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

void AProjectD_DefaultGameMode::CalcDestroyedObjectPrice(int32 price)
{
	CurScore += price;

	CountSlowStack();
}

void AProjectD_DefaultGameMode::SetCanSlow(bool _canSlow)
{
	UE_LOG(LogTemp, Display, TEXT("Can slow : %d"), CanSlow);
	CanSlow = _canSlow;
}

void AProjectD_DefaultGameMode::CountSlowStack()
{
	if (IsInSlowCoolDown == false && CanSlow == true) {
		SlowTimedilation();
	}
	else {
		curSlowStack += 1;
	}

	if (curSlowStack >= MAX_SLOW_STACK - 1) {
		SetCanSlow(true);
	}
}

void AProjectD_DefaultGameMode::SlowTimedilation()
{
	if (IsInSlowCoolDown == true) return;

	InitSlowStack();

	IsInSlowCoolDown = true;
	GetWorld()->GetWorldSettings()->SetTimeDilation(TIMEDILATION_SLOW);

	//N초 후 딜레이션 원복하기 -> 타임매니저
	GetWorldTimerManager().SetTimer(
		RollbackTimedilationHandle, 
		this, 
		&AProjectD_DefaultGameMode::RollbackTimedilation,
		DURATION_SLOW * TIMEDILATION_SLOW, 
		false
	);
}

void AProjectD_DefaultGameMode::RollbackTimedilation()
{
	GetWorld()->GetWorldSettings()->SetTimeDilation(TIMEDILATION_DEFAULT);

	GetWorldTimerManager().SetTimer(
		CoolDownSlowHandle,
		this,
		&AProjectD_DefaultGameMode::InitIsInSlowCoolDown,
		COOLDOWN_SLOW,
		false
	);
}

void AProjectD_DefaultGameMode::InitIsInSlowCoolDown()
{
	IsInSlowCoolDown = false;
}

void AProjectD_DefaultGameMode::InitSlowStack()
{
	SetCanSlow(false);
	curSlowStack = 0;
}

#pragma region Object Pool

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

#pragma endregion
