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
	for (auto& e : ObjectPoolingActorClass)
	{
		ObjectPool.Add(e.Key, TArray<AActor*>());
		for (auto i = 0; i < e.Value; i++)
		{
			CreateObject(e.Key);
		}
	}
}

TScriptInterface<IObjectPoolable> UObjectPoolSubsystem::RequestObjectFromPool(UClass* ActorClass)
{
	TScriptInterface<IObjectPoolable> Result;

	if (ObjectPool.Contains(ActorClass))
	{
		if (ObjectPool[ActorClass].Num() < 1)
		{
			UE_LOG(LogTemp, Display, TEXT("There is no Object. Need to create more object!"));
			CreateObject(ActorClass);
		}

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

void UObjectPoolSubsystem::CreateObject(UClass* ActorClass)
{
	FActorSpawnParameters params = FActorSpawnParameters();
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AActor* Actor = GetWorld()->SpawnActor<AActor>(ActorClass, FVector::ZeroVector, FRotator::ZeroRotator, params);
	if (Actor && Actor->GetClass()->ImplementsInterface(UObjectPoolable::StaticClass()))
	{
		IObjectPoolable* Poolable = Cast<IObjectPoolable>(Actor);
		if (Poolable)
		{
			Poolable->Deactivate();
		}

		ObjectPool[ActorClass].Add(Actor);
	}
}
