// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProjectD_DefaultGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API AProjectD_DefaultGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
    AProjectD_DefaultGameMode();
    virtual void BeginPlay() override;
protected:
    virtual void Tick(float deltaTime) override;

public:
    //UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FadeIn")
    //float FadeInDelay = 0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FadeIn")
    float FadeInValue = 0;
private:
    FTimerHandle FadeInHandle;
    bool bCanFadeIn = false;

    void SetCanFadeIn();
    void FadeIn(float dt);

#pragma region Game Condition

public:
    float ElapsedGameTime = 0;
    int32 TotalObjectPrice = 0;
    int32 Phase1_ClearPrice = 0;
    int32 Phase2_ClearPrice = 0;

    const float PHASE1_CLEAR_PERCENTAGE = 0.4;
    const float PHASE2_CLEAR_PERCENTAGE = 0.6;
private:
    void CalcAllObjectPriceInWorld();

#pragma endregion

#pragma region Object Pool

public:
    // The object pool
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class AObjectPoolSystem* ObjectPoolSystem_NsDisplay;
private:
    // The class of the pooled actor
    UPROPERTY(EditDefaultsOnly, Category = "Pooling|NsDisplay")
    TSubclassOf<class ANsDisplay> PoolTargetClass_NsDisplay;
    // The size of the pool
    UPROPERTY(EditDefaultsOnly, Category = "Pooling|NsDisplay")
    int32 PoolSize_NsDisplay;

private:
    void InitObjectPool_NsDisplay();
    UFUNCTION(BlueprintCallable)
    class ANsDisplay* Get_NsDisplay();
    UFUNCTION(BlueprintCallable)
    void Return_NsDisplay(class ANsDisplay* _NsDisplay);
#pragma endregion

};
