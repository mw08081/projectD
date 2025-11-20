// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ObjectPoolSubsystem.generated.h"

class IObjectPoolable;
/**
 * 
 */

UCLASS(Blueprintable)
class PROJECTD_API UObjectPoolSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	UObjectPoolSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	TMap<TSubclassOf<AActor>, TArray<AActor*>> ObjectPool;

public:
	void InitObjectPool(TMap<TSubclassOf<AActor>, int32> ObjectPoolingActorClass);

	UFUNCTION(BlueprintCallable)
	TScriptInterface<IObjectPoolable> RequestObjectFromPool(UClass* ActorClass);

	UFUNCTION(BlueprintCallable)
	void ReturnObjectToPool(TScriptInterface<IObjectPoolable> PoolableActor);


};
