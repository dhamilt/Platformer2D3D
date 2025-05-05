// Fill out your copyright notice in the Description page of Project Settings.


#include "OnRailsCharacter.h"
#include "InputActionValue.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/SplineComponent.h"
#include "Components/TimelineComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "OnRailsPlatformActor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AOnRailsCharacter::AOnRailsCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	cameraBoom->SetupAttachment(RootComponent);

	followCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	followCamera->SetupAttachment(cameraBoom, USpringArmComponent::SocketName);
	
	/*const FDetachmentTransformRules detachmentRule(EDetachmentRule::KeepWorld, true);
	cameraBoom->DetachFromComponent(detachmentRule);*/
}

void AOnRailsCharacter::OnConstruction(const FTransform& transform)
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

// Called when the game starts or when spawned
void AOnRailsCharacter::BeginPlay()
{
	Super::BeginPlay();
	FVector startPosition = platformSplineRef.Get()->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
	startPosition += positionOffset;
	SetActorLocation(startPosition);

	int32 numOfSplinePoints = cameraSplineRef.Get()->GetNumberOfSplinePoints();
	FVector startCameraPosition = cameraSplineRef.Get()->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
	cameraBoom->SetWorldLocation(startCameraPosition);
	
	maxSplineDist = platformSplineRef.Get()->GetSplineLength();

	if (APlayerController* playerController = Cast<APlayerController>(GetController()))
	{
		// Set to static camera
		playerController->SetViewTargetWithBlend(this, 0.0);
		// Add input mapping context to player
		if (UEnhancedInputLocalPlayerSubsystem* enhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer()))
			enhancedInputSubsystem->AddMappingContext(inputMappingCxt, 0);
	}
}

// Called every frame
void AOnRailsCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	cachedDeltaTime = DeltaTime;
}

// Called to bind functionality to input
void AOnRailsCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AOnRailsCharacter::Move);
	}
}

void AOnRailsCharacter::Move(const FInputActionValue& value)
{
	// Get input
	float inputDir = value.Get<float>();
	if((distanceOnSpline > 0.0f && -inputDir < 0.0f) || (distanceOnSpline < maxSplineDist && -inputDir > 0.0f))
	{ 
		// Move Character on spline
		distanceOnSpline += characterSpeed * 0.6f * -inputDir;
		FVector playerLocation = platformSplineRef.Get()->GetLocationAtDistanceAlongSpline(distanceOnSpline, ESplineCoordinateSpace::World);
		FVector playerTangent = platformSplineRef.Get()->GetTangentAtDistanceAlongSpline(distanceOnSpline, ESplineCoordinateSpace::World);
		FRotator playerRot = UKismetMathLibrary::MakeRotFromX(playerTangent * -inputDir);
		FRotator playerRotWithOffset = FRotator(playerRot.Pitch, playerRot.Yaw + orientationOffset.Yaw, playerRot.Roll);
		
		
		FVector pos = GetCapsuleComponent()->GetComponentLocation();
		FVector dir = (playerLocation + positionOffset) - pos;
		dir.Normalize();
		
		AddMovementInput(dir,  characterSpeed* 7500);
		GetMesh()->SetWorldRotation(playerRotWithOffset);
		// Move camera on rails
		FVector cameraLocation = cameraSplineRef.Get()->GetLocationAtDistanceAlongSpline(distanceOnSpline * 0.995f, ESplineCoordinateSpace::World);
		FVector cameraTangent = cameraSplineRef.Get()->GetTangentAtDistanceAlongSpline(distanceOnSpline * 0.995f, ESplineCoordinateSpace::World);
		FRotator cameraRot = UKismetMathLibrary::MakeRotFromX(cameraTangent);
		FRotator cameraRotWithOffset = FRotator(cameraRot.Pitch, cameraRot.Yaw + 90.0f, cameraRot.Roll);

		cameraBoom->SetWorldLocation(cameraLocation);
		cameraBoom->SetWorldRotation(cameraRotWithOffset);
		}
}

