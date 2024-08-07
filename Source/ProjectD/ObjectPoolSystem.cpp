// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPoolSystem.h"

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
	
}

void AObjectPool::InitializePool(TSubclassOf<AActor> ActorClass, int32 InPoolSize)
{
    PooledActorClass = ActorClass;
    PoolSize = InPoolSize;

    for (int32 i = 0; i < PoolSize; ++i)
    {
        AActor* NewActor = GetWorld()->SpawnActor<AActor>(PooledActorClass);
        NewActor->SetActorHiddenInGame(true);
        NewActor->SetActorEnableCollision(false);
        Pool.Add(NewActor);
    }
}

