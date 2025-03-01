// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/FloatingScore.h"
#include "Kismet/GameplayStatics.h"
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

	TextRenderComponent->SetText(FText::FromString(FString::FromInt(Score)));
	SetDetails(Location);
}


void AFloatingScore::SetDetails(FVector Location)
{

}

