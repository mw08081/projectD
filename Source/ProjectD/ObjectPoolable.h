// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ObjectPoolable.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType, MinimalAPI)
class UObjectPoolable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTD_API IObjectPoolable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Activate() = 0;
	virtual void Deactivate() = 0;
};
