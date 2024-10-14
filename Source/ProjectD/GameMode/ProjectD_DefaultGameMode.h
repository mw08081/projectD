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

    // 클리어 점수 변수
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
    int32 TotalObjectPrice = 0;
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
    int32 Phase1_ClearScore = 0;
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
    int32 Phase2_ClearScore = 0;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
    int32 CurScore = 0;
private:
    // 클리어 점수 변수
    const float PHASE1_CLEAR_PERCENTAGE = 0.4;
    const float PHASE2_CLEAR_PERCENTAGE = 0.6;

    // 점수 보간 변수
    const float SCORE_INTERPOL_DURATION_RATE = 0.002f;
    const float SCORE_INTERPOL_MIN_DURATION = 1;
    float ElapsedScoreInterpolTime = 0;
    float ScoreInterpolDuration;
    int32 ScoreInterpolStartVal;
    int32 InterpolTargetScore;
public:
    // 클리어 조건 함수
    UFUNCTION(BlueprintCallable)
    void GetScore(int32 price);
private:
    // 클리어 조건 함수
    void CalcAllObjectPriceInWorld();

    // 점수 보간
    void InterpolateScore(float dt);
    
#pragma endregion

#pragma region Slow

public:
    /// <summary>
    /// CanSlow 는 더이상 BlowSlow와 연관이 없으며, BlowSlow는 사라졌습니다.
    /// 강타가능시, 직접적으로 SlowTimedilation()을 호출하며, 
    /// CanSlow는 일정 조건을 달성해야만 SlowTimedilation()를 호출할수있습니다.
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool CanSlow = false;
private:
    // 슬로우 관련 변수
    /// <summary>
    /// n초 이내로, CurSlowStack이 MAX_SLOW_STACK을 이상이되면 slow 발동
    /// </summary>
    FTimerHandle InitSlowStackHandle;
    FTimerHandle RollbackTimedilationHandle;
    FTimerHandle CoolDownSlowHandle;

    const float COOLDOWN_SLOW = 15;
    const float DURATION_SLOW = 3;
    const float TIMEDILATION_DEFAULT = 1;
    const float TIMEDILATION_SLOW = 0.25;

    const int32 MAX_SLOW_STACK = 4;
    int32 curSlowStack = 0;

    bool IsInSlowCoolDown = false;

public:
    UFUNCTION(BlueprintCallable)
    void SlowTimedilation();
private:
    // 슬로우 함수
    void SetCanSlow(bool _canSlow);
    void CountSlowStack();

    void RollbackTimedilation();
    void InitIsInSlowCoolDown();

    void InitSlowStack();

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
