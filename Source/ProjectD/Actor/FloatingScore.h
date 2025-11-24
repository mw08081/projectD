// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "ObjectPoolable.h"

#include "FloatingScore.generated.h"

UCLASS()
class PROJECTD_API AFloatingScore : public AActor, public IObjectPoolable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingScore();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:

protected:
private:
	UPROPERTY(VisibleDefaultsOnly)
	class UTextRenderComponent* TextRenderComponent;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Move")
	float MoveSpeed = 10.0;

protected:
private:
	const float SpawningLifeTimeThreshold = 1.0f;

	bool IsSpawn = false;
	float ElapasedSpawnTime = 0.0;

public:
	UFUNCTION(BlueprintCallable)
	void Init(FVector Location, int32 score);
	
	UFUNCTION(BlueprintCallable)
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable)
	virtual void Deactivate() override;
protected:
private:
	void Moving(float DeltaTime);
	void ReturnToObjectPoolSubsystem();

	void SetDetails(FVector Location, int32 score);
	FString FormattingValue(FString Value);

};
