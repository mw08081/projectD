// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "ObjectPoolable.h"

#include "FracturedPiece.generated.h"

UCLASS()
class PROJECTD_API AFracturedPiece : public AActor, public IObjectPoolable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFracturedPiece();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "Component")
	TObjectPtr<class UStaticMeshComponent> Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component")
	TObjectPtr<class ULvObjectRoot> LvObjectRoot;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable)
	virtual void Deactivate() override;

};
