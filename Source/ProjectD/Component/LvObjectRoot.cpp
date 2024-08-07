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

	static ConstructorHelpers::FClassFinder<UGameInstance> GameInstanceBPClass(TEXT("/Game/System/Manager/BP_GameInstance"));
	if (GameInstanceBPClass.Class != nullptr)
	{
		BP_GameInstanceClass = GameInstanceBPClass.Class;
	}
}


// Called when the game starts
void ULvObjectRoot::BeginPlay()
{
	Super::BeginPlay();

	// ...
    //CalcObjectPrice();
}

void ULvObjectRoot::CalcObjectPrice()
{
    // Get the GameInstance
    UGameInstance* GameInstance = GetWorld()->GetGameInstance();

    if (GameInstance && GameInstance->IsA(BP_GameInstanceClass))
    {
        // Cast to the BP_GameInstance
        UObject* BP_GameInstance = Cast<UObject>(GameInstance);

        if (BP_GameInstance)
        {
            // Call the custom function in BP_GameInstance
            static FName FunctionName(TEXT("CalcObjPrice"));
            UFunction* Function = BP_GameInstance->FindFunction(FunctionName);

            if (Function)
            {
                UE_LOG(LogTemp, Display, TEXT("call game instance func : %s"), FunctionName);
                BP_GameInstance->ProcessEvent(Function, nullptr);
            }
        }
    }
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

