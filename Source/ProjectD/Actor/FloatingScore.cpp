// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/FloatingScore.h"

#include "Kismet/GameplayStatics.h"
#include "Components/TextRenderComponent.h" 

#include "GameMode/ProjectD_DefaultGameMode.h"
#include "System/ObjectPoolSubsystem.h"

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
			ReturnToObjectPoolSubsystem();
		}
	}
}


void AFloatingScore::Moving(float DeltaTime)
{
	FVector CurLocation = GetActorLocation();
	CurLocation.Z += MoveSpeed * DeltaTime;
	
	SetActorLocation(CurLocation);
}

void AFloatingScore::ReturnToObjectPoolSubsystem()
{
	UObjectPoolSubsystem* ObjectPoolSubsystem = GetWorld()->GetSubsystem<UObjectPoolSubsystem>();
	if (ObjectPoolSubsystem == nullptr) return;

	ObjectPoolSubsystem->ReturnObjectToPool(this);
}

void AFloatingScore::Init(FVector Location, int32 Score)
{
	IsSpawn = true;

	APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	FVector PlayerDirection = Player->GetActorLocation() - Location;

	SetActorLocation(Location);
	SetActorRotation(PlayerDirection.Rotation());

	SetDetails(Location, Score);
}

void AFloatingScore::Activate()
{
	IsSpawn = true;

	SetActorHiddenInGame(false);
}

void AFloatingScore::Deactivate()
{
	IsSpawn = false;
	ElapasedSpawnTime = 0;

	SetActorHiddenInGame(true);
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

