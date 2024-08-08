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
        ANsDisplay* NewActor = GetWorld()->SpawnActor<ANsDisplay>(PoolTargetClass_NsDisplay);
        NewActor->SetActorHiddenInGame(true);
        ObjectPool_NsDisplay.Add(NewActor);
    }
}

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

    return nullptr;
}

ANsDisplay* AObjectPoolSystem::GetAddtionalObject_NsDisplay()
{
    ANsDisplay* addtionalNewNsDisplay = GetWorld()->SpawnActor<ANsDisplay>(PoolTargetClass_NsDisplay);
    addtionalNewNsDisplay->SetActorHiddenInGame(false);
    addtionalNewNsDisplay->SetActorTickEnabled(true);
    return addtionalNewNsDisplay;
}

void AObjectPoolSystem::ReturnPooledObject_NsDisplay(ANsDisplay* Ns_Display)
{
    Ns_Display->SetActorHiddenInGame(true);
}


