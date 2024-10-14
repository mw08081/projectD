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
	//FadeIn(deltaTime);

	InterpolateScore(deltaTime);
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
	//#include "EngineUtils.h" 을 이용한 액터 순회
	for (const AActor* ActorPtr : FActorRange(GetWorld()))
	{
		//액터 내의 lvObjectRoot 회수
		ULvObjectRoot* lvObjectRoot = ActorPtr->FindComponentByClass<ULvObjectRoot>();
		if (lvObjectRoot != nullptr) {
			TotalObjectPrice += lvObjectRoot->objectPrice;
		} 
	}

	Phase1_ClearScore = TotalObjectPrice * PHASE1_CLEAR_PERCENTAGE;
	Phase2_ClearScore = TotalObjectPrice * PHASE2_CLEAR_PERCENTAGE;
	UE_LOG(LogTemp, Display, TEXT("phase 1 : %d , phase 2: %d"), Phase1_ClearScore, Phase2_ClearScore);
}

void AProjectD_DefaultGameMode::GetScore(int32 price)
{
	// 새로운 보간의 시작 (시작 : 현재점수, 목표 : 현재점수 + price)
	ScoreInterpolStartVal = CurScore;
	InterpolTargetScore += price;

	// 보간값 초기화
	ElapsedScoreInterpolTime = 0;
	ScoreInterpolDuration = FMath::Max((FMath::Abs(ScoreInterpolStartVal - InterpolTargetScore) * SCORE_INTERPOL_DURATION_RATE),
									SCORE_INTERPOL_MIN_DURATION);

	CountSlowStack();
}

void AProjectD_DefaultGameMode::InterpolateScore(float dt)
{
	if (CurScore >= InterpolTargetScore) { 
		CurScore = InterpolTargetScore;
		return; 
	}
	ElapsedScoreInterpolTime += dt;

	//고정된 A to B의 Lerp
	CurScore = FMath::Lerp(ScoreInterpolStartVal, InterpolTargetScore, ElapsedScoreInterpolTime / ScoreInterpolDuration);
}


#pragma region Slow

void AProjectD_DefaultGameMode::SetCanSlow(bool _canSlow)
{
	CanSlow = _canSlow;
}

void AProjectD_DefaultGameMode::CountSlowStack()
{
	if (IsInSlowCoolDown == true) return;

	//1초 내로 n개 파괴 타이머 : 중복실행을 막기위한 IsTimerActive
	if (GetWorld()->GetWorld()->GetTimerManager().IsTimerActive(InitSlowStackHandle) == false) {
		GetWorldTimerManager().SetTimer(
			InitSlowStackHandle,
			this,
			&AProjectD_DefaultGameMode::InitSlowStack,
			1,
			false
		);
	}

	if (CanSlow == true) {
		SlowTimedilation();
	}
	else {
		curSlowStack += 1;
		//UE_LOG(LogTemp, Display, TEXT("stack slowstack : %d"), curSlowStack);
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

#pragma endregion

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
