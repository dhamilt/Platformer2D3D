// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "OnRailsCharacter.generated.h"

struct FInputActionValue;
class UTimelineComponent;
class UInputAction;
class UInputMappingContext;
class USplineComponent;
class UCameraComponent;
class USpringArmComponent;

UENUM(BlueprintType, Category = "OnRails")
enum class ESplineDirection :uint8
{
	X,
	Y,
	Z
};

UCLASS()
class PLATFORMER2D3D_API AOnRailsCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AOnRailsCharacter();

	virtual void OnConstruction(const FTransform& transform) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Allows Character to move along the spline
	void Move(const FInputActionValue& value);

private:
	float cachedDeltaTime;

	float distanceOnSpline = 0.0f;

	float maxSplineDist;

	UTimelineComponent* characterMoveAndCameraTrack;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OnRails")
	float characterSpeed = 5.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	// Reference to spline for camera rig pathing
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OnRails")
	TSoftObjectPtr<USplineComponent> cameraSplineRef;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OnRails")
	TSoftObjectPtr<USplineComponent> platformSplineRef;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "OnRails")
	TObjectPtr<USpringArmComponent> cameraBoom;

	UPROPERTY(BlueprintReadWrite,VisibleAnywhere, Category = "OnRails")
	TObjectPtr<UCameraComponent> followCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OnRails")
	ESplineDirection splineDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* inputMappingCxt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OnRails")
	FVector positionOffset = FVector(150.0f, 0.0f, 300.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OnRails")
	FRotator orientationOffset = FRotator(0.0f, 0.0f, 90.0f);

};
