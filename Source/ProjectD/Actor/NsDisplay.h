// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NsDisplay.generated.h"

UCLASS()
class PROJECTD_API ANsDisplay : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANsDisplay();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
