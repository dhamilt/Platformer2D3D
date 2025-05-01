// Fill out your copyright notice in the Description page of Project Settings.


#include "OnRailsPlatformActor.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "Components/MeshComponent.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Engine/StaticMesh.h"


// Sets default values
AOnRailsPlatformActor::AOnRailsPlatformActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	railsSpline = CreateDefaultSubobject<USplineComponent>(TEXT("Rails"));
	platformMeshSpline = CreateDefaultSubobject<USplineComponent>(TEXT("Platform Mesh Spline"));
	RootComponent = platformMeshSpline;
	railsSpline->AttachToComponent(platformMeshSpline, FAttachmentTransformRules::KeepRelativeTransform);
	followCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	followCamera->AttachToComponent(platformMeshSpline, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AOnRailsPlatformActor::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector AOnRailsPlatformActor::GetForwardSplineDirection()
{
	FVector result;

	switch (splineDirection)
	{
	case ESplineDirection::X:
		result = FVector::ForwardVector;
		break;

	case ESplineDirection::Y:
		result = FVector::RightVector;
		break;

	case ESplineDirection::Z:
		result = FVector::UpVector;
		break;

	default:
		result = FVector::ForwardVector;
		break;
	}
	return result;
}

// Called every frame
void AOnRailsPlatformActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOnRailsPlatformActor::OnConstruction(const FTransform& Transform)
{	
	int32 meshPoints = platformMeshSpline->GetNumberOfSplinePoints() - 1;

	for (int32 i = 0; i < meshPoints; ++i)
	{
		USplineMeshComponent* platformInst = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());
		
		platformInst->SetStaticMesh(meshInstance);
		platformInst->SetMobility(EComponentMobility::Movable);
		platformInst->CreationMethod = EComponentCreationMethod::SimpleConstructionScript;
		platformInst->AttachToComponent(platformMeshSpline, FAttachmentTransformRules::KeepRelativeTransform);
		platformInst->RegisterComponentWithWorld(GetWorld());
				
		
		FVector start, end;
		FVector startTangent, endTangent;
		platformMeshSpline->GetLocationAndTangentAtSplinePoint(i, start, startTangent, ESplineCoordinateSpace::Local);
		platformMeshSpline->GetLocationAndTangentAtSplinePoint(i + 1, end, endTangent, ESplineCoordinateSpace::Local);
		platformInst->SetStartAndEnd(start, startTangent, end, endTangent);
		platformInst->SetForwardAxis(ESplineMeshAxis::X);

		platformInst->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void AOnRailsPlatformActor::SetCameraRigFollowDirection(ESplineDirection splineDir)
{
}

