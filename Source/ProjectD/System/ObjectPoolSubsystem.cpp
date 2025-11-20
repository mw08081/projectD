// Fill out your copyright notice in the Description page of Project Settings.


#include "System/ObjectPoolSubsystem.h"

#include "ObjectPoolable.h"

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
	FActorSpawnParameters params = FActorSpawnParameters();
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (auto& e : ObjectPoolingActorClass)
	{
		ObjectPool.Add(e.Key, TArray<AActor*>());
		for (auto i = 0; i < e.Value; i++)
		{
			AActor* Actor = GetWorld()->SpawnActor<AActor>(e.Key, FVector::ZeroVector, FRotator::ZeroRotator, params);
			if (Actor && Actor->GetClass()->ImplementsInterface(UObjectPoolable::StaticClass()))
			{
				IObjectPoolable* Poolable = Cast<IObjectPoolable>(Actor);
				if (Poolable)
				{
					Poolable->Deactivate(); 
				}

				ObjectPool[e.Key].Add(Actor);
			}
		}
	}
}

TScriptInterface<IObjectPoolable> UObjectPoolSubsystem::RequestObjectFromPool(UClass* ActorClass)
{
	TScriptInterface<IObjectPoolable> Result;

	if (ObjectPool.Contains(ActorClass) && ObjectPool[ActorClass].Num() > 0)
	{
		AActor* Actor = ObjectPool[ActorClass].Pop();
		if (Actor && Actor->GetClass()->ImplementsInterface(UObjectPoolable::StaticClass()))
		{
			Result.SetObject(Actor);
			Result.SetInterface(Cast<IObjectPoolable>(Actor));

			IObjectPoolable* Poolable = Result.GetInterface();
			if (Poolable)
			{
				Poolable->Activate();
			}
		}
	}

	return Result;
}

void UObjectPoolSubsystem::ReturnObjectToPool(TScriptInterface<IObjectPoolable> PoolableActor)
{
	if (!PoolableActor) {
		return;
	}

	AActor* Actor = Cast<AActor>(PoolableActor.GetObject());
	if (!Actor) {
		return;
	}

	UClass* ActorClass = Actor->GetClass();
	ObjectPool[ActorClass].Add(Actor);

	PoolableActor.GetInterface()->Deactivate();
}
