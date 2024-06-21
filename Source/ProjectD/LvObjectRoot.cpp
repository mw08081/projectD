// Fill out your copyright notice in the Description page of Project Settings.


#include "LvObjectRoot.h"

// Sets default values for this component's properties
ULvObjectRoot::ULvObjectRoot()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void ULvObjectRoot::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULvObjectRoot::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int32 ULvObjectRoot::getObjectPrice()
{
	return objectPrice;
}

