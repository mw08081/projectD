// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectPoolSystem.generated.h"

UCLASS()
class PROJECTD_API AObjectPoolSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectPoolSystem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#pragma region Ns Display Object Pool
private:
	TSubclassOf<class ANsDisplay> PoolTargetClass_NsDisplay;

	// The pool of actors
	TArray<class ANsDisplay*> ObjectPool_NsDisplay;

	// The size of the pool
	int32 PoolSize_NsDisplay;

public:
	// Function to initialize the pool
	void InitializePool_NsDisplay(TSubclassOf<class ANsDisplay> _PoolTargetClass_NsDisplay, int32 _PoolSize_NsDisplay);
	
	UFUNCTION(BlueprintCallable)
	// Function to get an actor from the pool
	class ANsDisplay* GetPooledObject_NsDisplay();
	UFUNCTION(BlueprintCallable)
	class ANsDisplay* GetAddtionalObject_NsDisplay();

	// Function to return an actor to the pool
	UFUNCTION(BlueprintCallable)
	void ReturnPooledObject_NsDisplay(class ANsDisplay* Ns_Display);

#pragma endregion

};
