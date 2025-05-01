// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OnRailsPlatformActor.generated.h"

class UStaticMesh;
class USplineComponent;
class USplineMeshComponent;
class UMeshComponent;
class APawn;
class UCameraComponent;

UENUM(BlueprintType, Category = "OnRails")
enum class ESplineDirection :uint8
{
	X,
	Y,
	Z
};

UCLASS()
class PLATFORMER2D3D_API AOnRailsPlatformActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOnRailsPlatformActor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	// Tells the Camera Rig which axis to follow based on how far
	// the Pawn has moved on the Platform Mesh Spline
	UFUNCTION(BlueprintCallable, Category = "OnRails")
	void SetCameraRigFollowDirection(ESplineDirection splineDir);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector GetForwardSplineDirection();

private:
	TArray<USplineMeshComponent*> platformMeshCollection;

public:	
	UPROPERTY(EditAnywhere, Category = "OnRails")
	TObjectPtr<USplineComponent> railsSpline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OnRails")
	TObjectPtr<USplineComponent> platformMeshSpline;

	UPROPERTY(EditAnywhere, Category = "OnRails")
	TObjectPtr<APawn> playerInstance;

	UPROPERTY(EditAnywhere, Category = "OnRails")
	TObjectPtr<UCameraComponent> followCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OnRails")
	TObjectPtr<UStaticMesh> meshInstance;

	UPROPERTY(EditAnywhere, Category = "OnRails")
	bool bFollowPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OnRails")
	ESplineDirection splineDirection;
};
