// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/FracturedPiece.h"

#include "Component/LvObjectRoot.h"

// Sets default values
AFracturedPiece::AFracturedPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	LvObjectRoot = CreateDefaultSubobject<ULvObjectRoot>(TEXT("LvObjectRoot"));
}

// Called when the game starts or when spawned
void AFracturedPiece::BeginPlay()
{
	Super::BeginPlay();
	
	Mesh->SetSimulatePhysics(true);
}
