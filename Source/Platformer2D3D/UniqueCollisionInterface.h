// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UniqueCollisionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UUniqueCollisionInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * 
 */
class PLATFORMER2D3D_API IUniqueCollisionInterface
{
	GENERATED_IINTERFACE_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent,  Category= "UniqueCollision")
	void ActivateCollision();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent,  Category= "UniqueCollision")
	void DeactivateCollision();


};
