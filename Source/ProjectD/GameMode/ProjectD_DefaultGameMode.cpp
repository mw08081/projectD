// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/ProjectD_DefaultGameMode.h"

#include "GameFramework/WorldSettings.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

#include "EngineUtils.h"

#include "Component/LvObjectRoot.h"
#include "System/ObjectPoolSubsystem.h"
#include "Actor/FloatingScore.h"

#include "Controller/ProjectDPlayerController.h"


AProjectD_DefaultGameMode::AProjectD_DefaultGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AProjectD_DefaultGameMode::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Display, TEXT("GAMEMODE Init"));


	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (IsValid(PlayerController))
	{
		DefaultPlayerController = Cast<AProjectDPlayerController>(PlayerController);
	}
	
	
	CalcAllObjectPriceInWorld();

	GetWorldTimerManager().SetTimer(FadeInHandle, this, &AProjectD_DefaultGameMode::SetCanFadeIn, 10.f, false);
	
	UObjectPoolSubsystem* ObjectPoolSubsystem = GetWorld()->GetSubsystem<UObjectPoolSubsystem>();
	ObjectPoolSubsystem->InitObjectPool(ObjectPoolingActorClass);

	//InitCharacterMesh();
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
			//UE_LOG(LogTemp, Display, TEXT("%s price %d"), *(ActorPtr->GetName()), lvObjectRoot->objectPrice);
			TotalObjectPrice += lvObjectRoot->objectPrice;
		} 
	}

	Phase1_ClearScore = TotalObjectPrice * PHASE1_CLEAR_PERCENTAGE;
	Phase2_ClearScore = TotalObjectPrice * PHASE2_CLEAR_PERCENTAGE;
	UE_LOG(LogTemp, Display, TEXT("Total : %d, phase 1 : %d , phase 2: %d"), TotalObjectPrice, Phase1_ClearScore, Phase2_ClearScore);
}

void AProjectD_DefaultGameMode::CheckClearCondition()
{
	if (CurScore >= Phase1_ClearScore) {
		ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (PlayerCharacter)
		{
			// 호출할 함수 이름 지정
			FName SetAngerMode(TEXT("SetAngerMode"));

			// 플레이어 Pawn에서 UFunction 포인터 찾기
			UFunction* Function = PlayerCharacter->FindFunction(SetAngerMode);
			PlayerCharacter->FindFunction(SetAngerMode);
			if (Function)
			{
				EAngerMode phase2 = EAngerMode::Mad;
				PlayerCharacter->ProcessEvent(Function, &phase2);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("플레이어에서 함수 %s를 찾을 수 없습니다."), *SetAngerMode.ToString());
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("플레이어 Pawn을 찾을 수 없습니다."));
		}
	}
	else if (CurScore >= Phase2_ClearScore) {

	}
	else if (CurScore >= TotalObjectPrice) {

	}
}

void AProjectD_DefaultGameMode::SpawnFloatingScore(FVector Location, int32 Score)
{
	// get from subsystem


	//// 플로팅 스코어 렌더링
	//AFloatingScore* fs = Cast<AFloatingScore>(ObjectPool->GetPooledActor(EPooledActorType::FloatingScore));

	//if (fs != nullptr) {
	//	fs->Spawn(Location, Score);
	//}
	
}

/// <summary>
/// 점수 획득, 보간 트리거 
/// </summary>
/// <param name="price">획득점수</param>
void AProjectD_DefaultGameMode::GetScore(int32 Price)
{
	// 새로운 보간의 시작 (시작 : 현재점수, 목표 : 현재점수 + price)
	ScoreInterpolStartVal = CurScore;
	InterpolTargetScore += Price;

	// 보간값 초기화
	ElapsedScoreInterpolTime = 0;
	ScoreInterpolDuration = FMath::Min((FMath::Abs(ScoreInterpolStartVal - InterpolTargetScore) * SCORE_INTERPOL_DURATION_RATE),
									SOCRE_INTERPOL_MAX_DURATION);		//최댓값 필터
	ScoreInterpolDuration = FMath::Max(ScoreInterpolDuration, SCORE_INTERPOL_MIN_DURATION);		//최솟값 필터

	CountSlowStack();
}

/// <summary>
/// Tick함수에서 실행
/// CurScore이 InterpolTargetScore보다 작을때만 실행(GetScore 실행시 Trigger)
/// </summary>
/// <param name="dt">DeltaTime</param>
void AProjectD_DefaultGameMode::InterpolateScore(float dt)
{
	if (CurScore >= InterpolTargetScore) { 
		CurScore = InterpolTargetScore;
		return; 
	}
	ElapsedScoreInterpolTime += dt;

	//고정된 A to B의 Lerp
	CurScore = FMath::Lerp(ScoreInterpolStartVal, InterpolTargetScore, ElapsedScoreInterpolTime / ScoreInterpolDuration);
	DefaultPlayerController->UpdateTxtScore(CurScore);

	CheckClearCondition();
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
