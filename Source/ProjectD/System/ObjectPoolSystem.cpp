// Fill out your copyright notice in the Description page of Project Settings.


#include "System/ObjectPoolSystem.h"
#include "Actor/NsDisplay.h"

// Sets default values
AObjectPoolSystem::AObjectPoolSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AObjectPoolSystem::BeginPlay()
{
	Super::BeginPlay();
    //InitializePool_NsDisplay(PoolTargetClass_NsDisplay, PoolSize_NsDisplay);
}

/// <summary>
/// pool 초기화
/// </summary>
/// <param name="ActorClasses"></param>
/// <param name="spawnCounts"></param>
void AObjectPoolSystem::InitPool(TArray<TSubclassOf<class AActor>> ActorClasses, TArray<int> SpawnCounts)
{
    if (ActorClasses.Num() != SpawnCounts.Num()) {
        UE_LOG(LogTemp,Error, TEXT("Pool Init Error :TSubclassOf class length != SpawnCount length"))
        return;
    }

    // 차후 추가생성을 위한 클래스 저장
    PoolingTargetClasses = ActorClasses;
    for (auto ActorClass : ActorClasses) {

        int32 idx = 0;

        TArray<AActor*> Row;
        for (int32 i = 0; i < SpawnCounts[idx]; i++) {
            AActor* Actor = GetWorld()->SpawnActor(ActorClass);
            Actor->SetActorHiddenInGame(true);

            Row.Add(Actor);
        }
        Pool.Add(Row);
        idx++;
    }
}

AActor* AObjectPoolSystem::GetPooledActor(EPooledActorType PooledActorType)
{
    uint8 idx = static_cast<uint8>(PooledActorType);

    for (AActor* Actor : Pool[idx]) {
        if (Actor->IsHidden()) {
            // make it active
            Actor->SetActorHiddenInGame(false);
            Actor->SetActorTickEnabled(true);

            return Actor;
        }
    }

    return GetAdditionalPooledActor(PooledActorType);
}

void AObjectPoolSystem::ReturnActor(AActor* ReturnedActor)
{
    ReturnedActor->SetActorHiddenInGame(true);
}

AActor* AObjectPoolSystem::GetAdditionalPooledActor(EPooledActorType PooledActorType)
{
    uint8 idx = static_cast<uint8>(PooledActorType);

    // 생성 후 삽입
    AActor* Actor = GetWorld()->SpawnActor(PoolingTargetClasses[idx]);
    Pool[idx].Add(Actor);

    return Actor;
}




/// <summary>
/// 풀 초기화
/// </summary>
/// <param name="_PoolTargetClass_NsDisplay"></param>
/// <param name="_PoolSize_NsDisplay"></param>
void AObjectPoolSystem::InitializePool_NsDisplay(TSubclassOf<ANsDisplay> _PoolTargetClass_NsDisplay, int32 _PoolSize_NsDisplay)
{
    PoolTargetClass_NsDisplay = _PoolTargetClass_NsDisplay;
    PoolSize_NsDisplay = _PoolSize_NsDisplay;

    for (int32 i = 0; i < PoolSize_NsDisplay; ++i)
    {
        ANsDisplay* NewActor = GetWorld()->SpawnActor<ANsDisplay>(PoolTargetClass_NsDisplay);
        NewActor->SetActorHiddenInGame(true);
        ObjectPool_NsDisplay.Add(NewActor);
    }
}

/// <summary>
/// 풀 받아오기
/// </summary>
/// <returns>사용가능한 액터</returns>
ANsDisplay* AObjectPoolSystem::GetPooledObject_NsDisplay()
{
    for (ANsDisplay* nsDisplay : ObjectPool_NsDisplay)
    {
        if (nsDisplay->IsHidden())
        {
            nsDisplay->SetActorHiddenInGame(false);
            nsDisplay->SetActorTickEnabled(true);
            return nsDisplay;
        }
    }

    return GetAddtionalObject_NsDisplay();
}

/// <summary>
/// 사용가능한 풀이 없을 경우
/// </summary>
/// <returns>추가 액터</returns>
ANsDisplay* AObjectPoolSystem::GetAddtionalObject_NsDisplay()
{
    ANsDisplay* addtionalNewNsDisplay = GetWorld()->SpawnActor<ANsDisplay>(PoolTargetClass_NsDisplay);
    addtionalNewNsDisplay->SetActorHiddenInGame(false);
    addtionalNewNsDisplay->SetActorTickEnabled(true);
    return addtionalNewNsDisplay;
}

/// <summary>
/// 액터 사용완료 후, 풀로 반환
/// </summary>
/// <param name="Ns_Display"></param>
void AObjectPoolSystem::ReturnPooledObject_NsDisplay(ANsDisplay* Ns_Display)
{
    Ns_Display->SetActorHiddenInGame(true);
}


