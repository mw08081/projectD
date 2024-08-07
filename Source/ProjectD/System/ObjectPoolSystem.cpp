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
    InitializePool_NsDisplay(PoolTargetClass_NsDisplay, PoolSize_NsDisplay);
}

void AObjectPoolSystem::InitializePool_NsDisplay(TSubclassOf<ANsDisplay> _PoolTargetClass_NsDisplay, int32 _PoolSize_NsDisplay)
{
    PoolTargetClass_NsDisplay = _PoolTargetClass_NsDisplay;
    PoolSize_NsDisplay = _PoolSize_NsDisplay;

    for (int32 i = 0; i < PoolSize_NsDisplay; ++i)
    {
        UE_LOG(LogTemp, Display, TEXT("%d 'nd ns display"), i);
        ANsDisplay* NewActor = GetWorld()->SpawnActor<ANsDisplay>(PoolTargetClass_NsDisplay);
        NewActor->SetActorHiddenInGame(true);
        NewActor->SetActorEnableCollision(false);
        ObjectPool_NsDisplay.Add(NewActor);
    }
}

ANsDisplay* AObjectPoolSystem::GetPooledObject_NsDisplay()
{
	return nullptr;
}

void AObjectPoolSystem::ReturnPooledObject_NsDisplay(ANsDisplay* Ns_Display)
{
}


