// Fill out your copyright notice in the Description page of Project Settings.


#include "System/ObjectPoolSubsystem.h"

UObjectPoolSubsystem::UObjectPoolSubsystem()
{

}

void UObjectPoolSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
}

void UObjectPoolSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UObjectPoolSubsystem::InitObjectPool(TMap<TSubclassOf<AActor>, int32> ObjectPoolingActorClass)
{
	UE_LOG(LogTemp, Display, TEXT("ObjectPoolSubsystem Initialize -> Pooling Target count : %d"), ObjectPoolingActorClass.Num());

	FActorSpawnParameters params = FActorSpawnParameters();
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (auto& e : ObjectPoolingActorClass)
	{
		ObjectPool.Add(e.Key, TArray<AActor*>());
		for (auto i = 0; i < e.Value; i++)
		{
			AActor* Actor = GetWorld()->SpawnActor<AActor>(e.Key, FVector::ZeroVector, FRotator::ZeroRotator, params);
			if (Actor)
			{
				Actor->SetActorHiddenInGame(true);
				Actor->SetActorEnableCollision(false);
				//

				ObjectPool[e.Key].Add(Actor);
			}
		}
	}
}
