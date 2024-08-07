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

public:
	UPROPERTY(EditDefaultsOnly, Category = "PoolingClass")
	TSubclassOf<class ANs> PoolTarget_NsClass;

private:
	TArray<ANs*> Ns_Pool;
	int32 Ns_PoolSize = 100;
};
