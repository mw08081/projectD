// Fill out your copyright notice in the Description page of Project Settings.
#include "LvObjectRoot.h"

#include "Engine/GameInstance.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values for this component's properties
ULvObjectRoot::ULvObjectRoot()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void ULvObjectRoot::BeginPlay()
{
	Super::BeginPlay();

}

