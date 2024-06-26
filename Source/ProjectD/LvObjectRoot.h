// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LvObjectRoot.generated.h"

UENUM(BlueprintType)
enum class EObjectType : uint8 
{ 
	None				UMETA(DisplayName = "None"),
	Static				UMETA(DisplayName = "Static"),
	FracturingObject	UMETA(DisplayName = "FracturingObject"),
	ConvertingObject	UMETA(DisplayName = "ConvertingObject"),
	DisappearingObject	UMETA(DisplayName = "DisappearingObject")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTD_API ULvObjectRoot : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULvObjectRoot();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void CalcObjectPrice();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EObjectType objectType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 objectPrice;
	UFUNCTION(BlueprintCallable)
		int32 getObjectPrice();




private:
	// Variable to store the BP_GameInstance class reference
	UClass* BP_GameInstanceClass;
};
