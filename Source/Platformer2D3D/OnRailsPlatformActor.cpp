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
	followCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
}

// Called when the game starts or when spawned
void AOnRailsPlatformActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOnRailsPlatformActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOnRailsPlatformActor::OnConstruction(const FTransform& Transform)
{
	///*if (!platformMeshCollection.IsEmpty())
	//	platformMeshCollection.Empty();*/

	//int32 meshPoints = platformMeshSpline->GetNumberOfSplinePoints() - 2;

	//for (int32 i = 0; i < meshPoints; ++i)
	//{
	//	FString str = "Platform#" + (i + 1);
	//	USplineMeshComponent* platformInst = CreateDefaultSubobject<USplineMeshComponent>(*str);
	//	platformInst->SetStaticMesh(meshInstance);
	//	FVector start, end;
	//	FVector startTangent, endTangent;
	//	platformMeshSpline->GetLocationAndTangentAtSplinePoint(i, start, startTangent, ESplineCoordinateSpace::World);
	//	platformMeshSpline->GetLocationAndTangentAtSplinePoint(i + 1, end, endTangent, ESplineCoordinateSpace::World);
	//	platformInst->SetStartAndEnd(start, startTangent, end, endTangent);
	//	platformMeshCollection.Add(platformInst);
	//}
}

