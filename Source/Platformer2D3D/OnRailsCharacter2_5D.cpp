// Fill out your copyright notice in the Description page of Project Settings.


#include "OnRailsCharacter2_5D.h"
#include "Components/StaticMeshComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "OnRailsPlatformActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AOnRailsCharacter2_5D::AOnRailsCharacter2_5D()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	followCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("followCamera"));
	followCamera->SetupAttachment(RootComponent);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
}

// Called when the game starts or when spawned
void AOnRailsCharacter2_5D::BeginPlay()
{
	Super::BeginPlay();
	FVector startPosition = platformSplineRef.Get()->GetLocationAtSplinePoint(1, ESplineCoordinateSpace::World);
	startPosition += positionOffset;
	SetActorLocation(startPosition);
	FVector cameraPosition = cameraSplineRef.Get()->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
	followCamera->SetWorldLocation(cameraPosition);

	if (APlayerController* pc = Cast<APlayerController>(GetController()))
	{
		// Set to static camera
		pc->SetViewTargetWithBlend(this, 0.0);

		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer()))
		{
			subsystem->AddMappingContext(mappingContext, 0);
		}
	}
}

void AOnRailsCharacter2_5D::OnConstruction(const FTransform& Transform)
{
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AOnRailsPlatformActor::StaticClass(), actors);
	if (!actors.IsEmpty())
	{
		AOnRailsPlatformActor* temp = Cast<AOnRailsPlatformActor>(actors[0]);
		cameraSplineRef = temp->railsSpline;
		platformSplineRef = temp->platformMeshSpline;
	}
}

// Called every frame
void AOnRailsCharacter2_5D::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOnRailsCharacter2_5D::Move(const FInputActionValue& value)
{
	// Get input
		float inputDir = value.Get<float>();
		
	if ((distanceOnSpline > 0.0f && -inputDir < 0.0f) || (distanceOnSpline < maxSplineDist && -inputDir > 0.0f))
	{
		// Move Character on spline
		//distanceOnSpline += characterSpeed * 0.6f * -inputDir;
		//FVector playerLocation = platformSplineRef.Get()->GetLocationAtDistanceAlongSpline(distanceOnSpline, ESplineCoordinateSpace::World);
		//FVector playerTangent = platformSplineRef.Get()->GetTangentAtDistanceAlongSpline(distanceOnSpline, ESplineCoordinateSpace::World);
		//FRotator playerRot = UKismetMathLibrary::MakeRotFromX(playerTangent * -inputDir);
		//FRotator playerRotWithOffset = FRotator(playerRot.Pitch, playerRot.Yaw + orientationOffset.Yaw, playerRot.Roll);


		//FVector pos = charMesh->GetComponentLocation();
		//FVector dir = (playerLocation + positionOffset) - pos;
		//dir.Normalize();

		//AddMovementInput(dir, characterSpeed * 7500);
		//charMesh->SetWorldLocation(positionOffset);
		//// Move camera on rails
		//FVector cameraLocation = cameraSplineRef.Get()->GetLocationAtDistanceAlongSpline(distanceOnSpline * 0.995f, ESplineCoordinateSpace::World);
		//FVector cameraTangent = cameraSplineRef.Get()->GetTangentAtDistanceAlongSpline(distanceOnSpline * 0.995f, ESplineCoordinateSpace::World);
		//FRotator cameraRot = UKismetMathLibrary::MakeRotFromX(cameraTangent);
		//FRotator cameraRotWithOffset = FRotator(cameraRot.Pitch, cameraRot.Yaw + 90.0f, cameraRot.Roll);

	
	}
}

void AOnRailsCharacter2_5D::JumpInput(const FInputActionValue& val)
{
}

// Called to bind functionality to input
void AOnRailsCharacter2_5D::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		input->BindAction(moveAction, ETriggerEvent::Triggered, this, &AOnRailsCharacter2_5D::Move);

		input->BindAction(jumpAction, ETriggerEvent::Triggered, this, &AOnRailsCharacter2_5D::JumpInput);
	}
}

