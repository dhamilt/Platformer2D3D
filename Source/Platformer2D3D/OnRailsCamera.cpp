// Fill out your copyright notice in the Description page of Project Settings.


#include "OnRailsCamera.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AOnRailsCamera::AOnRailsCamera(const FObjectInitializer& initializer): ACineCameraRigRail(initializer)
{
	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	springArm->SetupAttachment(GetDefaultAttachComponent());
	springArm->TargetArmLength = 10;
	springArm->bEnableCameraLag = true;
	
	
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(springArm);
	bAllowTickBeforeBeginPlay = false;
}

// Called when the game starts or when spawned
void AOnRailsCamera::BeginPlay()
{
	Super::BeginPlay();
	if (trackActorRef && !GEditor->IsSimulateInEditorInProgress())
		FindPawnActorToTrack();

	if (APlayerController* pc = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		pc->SetViewTargetWithBlend(this);
}

// Called every frame
void AOnRailsCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isTrackingActorOnSpline)
	{
		if (!trackActorRef && !GEditor->IsSimulateInEditorInProgress())
			FindPawnActorToTrack();
		if (USplineComponent* spline = GetRailSplineComponent())
		{
			if (trackActorRef)
			{
				target = trackActorRef->GetActorLocation();
				FVector pos = spline->FindLocationClosestToWorldLocation(target, ESplineCoordinateSpace::World) + positionOffset;
				springArm->SetWorldLocation(pos);
				cameraRot = camera->GetComponentRotation();
				cameraRot.Yaw = UKismetMathLibrary::FindLookAtRotation(pos, target).Yaw;
				camera->SetWorldRotation(cameraRot);
			}
		}
	}
}

void AOnRailsCamera::FindPawnActorToTrack()
{
	TArray<AActor*> pawns;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), actorToTrack, pawns);
	if (!pawns.IsEmpty())
		trackActorRef = pawns[0];
}

