// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "OnRailsCharacter2_5D.generated.h"

class UCameraComponent;
class USplineComponent;
class UStaticMeshComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;


UCLASS()
class PLATFORMER2D3D_API AOnRailsCharacter2_5D : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AOnRailsCharacter2_5D();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& val);

	void JumpInput(const FInputActionValue& val);

	virtual void OnConstruction(const FTransform& Transform) override;

private:
	float cachedDeltaTime;

	float distanceOnSpline = 0.0f;

	float maxSplineDist;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "2.5D Character")
	float orientationOffset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "2.5D Character")
	FVector positionOffset;

	

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "2.5D Character")
	UInputAction* moveAction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "2.5D Character")
	UInputAction* jumpAction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "2.5D Character")
	UInputMappingContext* mappingContext;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "2.5D Character")
	float characterSpeed  = 10;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OnRails")
	TSoftObjectPtr<USplineComponent> platformSplineRef;
};
