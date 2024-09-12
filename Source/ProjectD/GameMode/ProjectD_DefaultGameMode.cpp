// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/ProjectD_DefaultGameMode.h"
#include "System/ObjectPoolSystem.h"

AProjectD_DefaultGameMode::AProjectD_DefaultGameMode()
{

}

void AProjectD_DefaultGameMode::BeginPlay()
{
	Super::BeginPlay();
	InitObjectPool_NsDisplay();
}


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
