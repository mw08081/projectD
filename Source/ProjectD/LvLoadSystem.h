#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LvLoadSystem.generated.h"

UCLASS()
class PROJECTD_API ALvLoadSystem : public AActor
{
	GENERATED_BODY()
	
public:
	// 이 actor의 속성에 대한 기본값을 설정합니다.
	ALvLoadSystem();

protected:
	// 게임이 시작되거나 생성될 때 호출됩니다.
	virtual void BeginPlay() override;

public:
	// 매 프레임마다 호출됨
	virtual void Tick(float DeltaTime) override;
};
