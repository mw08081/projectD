#include "LvLoadSystem.h"
#include "JsonObjectConverter.h"
#include "UObject/SavePackage.h"

//#include "Runtime/CoreUObject/Public/UObject/UObjectIterator.h"
//#include "Runtime/Engine/Public/EngineUtils.h"
#include "EngineUtils.h"
#include "LvObjectRoot.h"

// 기본값 설정
ALvLoadSystem::ALvLoadSystem()
{
	// 모든 프레임에서 Tick()을 호출하도록 이 actor을(를) 설정합니다. 필요하지 않은 경우 이 기능을 해제하여 성능을 향상시킬 수 있습니다.
	PrimaryActorTick.bCanEverTick = true;

}

// 게임이 시작되거나 생성될 때 호출됩니다.
void ALvLoadSystem::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Display, TEXT("Lv Load Sys Init"));
	ReadLv();
}

// 매 프레임마다 호출됨
void ALvLoadSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Display, TEXT("hello world!"));
}

void ALvLoadSystem::ReadLv()
{
	UE_LOG(LogTemp, Display, TEXT("Read LV"));

	//const FString SaveDir = FPaths::Combine(FPlatformMisc::ProjectDir(), TEXT("Saved"));
	//UE_LOG(LogTemp, Display, TEXT("Save Dir : %s"), *SaveDir);

	//const FString JsonDataFileName(TEXT("LvData.txt"));
	//FString AbsolutePathForJsonData = FPaths::Combine(*SaveDir, JsonDataFileName);
	//UE_LOG(LogTemp, Display, TEXT("AbsolutePathForJsonData Dir : %s"), *AbsolutePathForJsonData);

	//FPaths::MakeStandardFilename(AbsolutePathForJsonData);
	//TSharedRef<FJsonObject> SrcJsonObject = MakeShared<FJsonObject>();
	////FJsonObjectConverter::UStructToJsonObject(Serialized)

	if (GetWorld())
	{
		for (TActorIterator<AActor> it(GetWorld()); it; ++it)
		{
			AActor* actor = *it;
			if (actor->FindComponentByClass<ULvObjectRoot>())
			{
				UE_LOG(LogTemp, Display, TEXT("static mesh comp : %s "), *actor->GetName());
			}
		}
	}
}
