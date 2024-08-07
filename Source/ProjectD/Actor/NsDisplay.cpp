// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/NsDisplay.h"

// Sets default values
ANsDisplay::ANsDisplay()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANsDisplay::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANsDisplay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

