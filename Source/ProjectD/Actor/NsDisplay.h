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
	ANsDisplay();

protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;

private:
	//components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* nsComponent;

public:
	UFUNCTION(BlueprintCallable)
	void SetNs(class UNiagaraSystem* ns);
};
