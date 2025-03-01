// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/FloatingScore.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/ProjectD_DefaultGameMode.h"
#include "System/ObjectPoolSystem.h"
#include "Components/TextRenderComponent.h" 

// Sets default values
AFloatingScore::AFloatingScore()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRender"));
	//RootComponent = TextRenderComponent;

	// 텍스트 설정
	TextRenderComponent->SetText(FText::FromString(TEXT("Hello, Unreal!")));

	// 텍스트 크기 설정
	TextRenderComponent->SetWorldSize(20.0f);

	// 텍스트 정렬 설정 (가운데 정렬)
	TextRenderComponent->SetHorizontalAlignment(EHTA_Center);
}

// Called when the game starts or when spawned
void AFloatingScore::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloatingScore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsSpawn) {
		if (SpawningLifeTimeThreshold > ElapasedSpawnTime) {
			ElapasedSpawnTime += DeltaTime;

			Moving(DeltaTime);
		}
		else {
			ElapasedSpawnTime = 0;
			IsSpawn = false;

			// Return To Pool // 풀 메소드 사용하지않고, 자체적으로 처리 // 비정형
			SetActorHiddenInGame(true);
			 
			//// 풀에 스폰과 리턴 메소드를 사용할 경우, 좀 더 정형화된 코드 (지저분..)
			//AProjectD_DefaultGameMode* GameMode = Cast<AProjectD_DefaultGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

			//if (GameMode == nullptr) {
			//	GameMode->ObjectPool->ReturnActor(this);
			//}
		}
	}
}


void AFloatingScore::Moving(float DeltaTime)
{
	FVector CurLocation = GetActorLocation();
	CurLocation.Z += MoveSpeed * DeltaTime;
	
	SetActorLocation(CurLocation);
}

void AFloatingScore::Spawn(FVector Location, int32 Score)
{
	IsSpawn = true;

	APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	FVector PlayerDirection = Player->GetActorLocation() - Location;

	SetActorLocation(Location);
	SetActorRotation(PlayerDirection.Rotation());

	SetDetails(Location, Score);
}


void AFloatingScore::SetDetails(FVector Location, int32 Score)
{
	FString FScore = FString::FromInt(Score);
	//FScore = FormattingValue(FScore);


	TextRenderComponent->SetText(FText::FromString(FScore));
}

FString AFloatingScore::FormattingValue(FString Value)
{
	TArray<char> FormattedValue;

	int idx = 0;
	for (int32 i = Value.Len() - 1 ; i >= 0; i--, idx++) {
		if (idx % 3 == 2) {
			
		}
		else {

		}
	}
	return FString();
}

