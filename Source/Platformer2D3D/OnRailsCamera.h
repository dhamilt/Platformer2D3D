// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CineCameraRigRail.h"
#include "OnRailsCamera.generated.h"

class UCameraComponent;
class USpringArmComponent;


UCLASS(Blueprintable)
class PLATFORMER2D3D_API AOnRailsCamera : public ACineCameraRigRail
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOnRailsCamera(const FObjectInitializer& initializer);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FindPawnActorToTrack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector target;
	FRotator cameraRot;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OnRails")
	UCameraComponent* camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OnRails")
	USpringArmComponent* springArm;

	UPROPERTY(BlueprintReadWrite, Category = "OnRails")
	bool isTrackingActorOnSpline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OnRails")
	TSubclassOf<APawn> actorToTrack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category =  "OnRails")
	FVector positionOffset;

	TObjectPtr<AActor> trackActorRef;
};
