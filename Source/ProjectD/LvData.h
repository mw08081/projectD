#pragma once
#include "LvData.generated.h"

USTRUCT(BlueprintType)
struct FLvObject
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ObjctName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector rotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector scale;
};

USTRUCT(BlueprintType)
struct FLvData
{
	GENERATED_USTRUCT_BODY()
public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FLvObject> LvDataArray;
};