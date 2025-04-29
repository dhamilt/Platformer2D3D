// Copyright Epic Games, Inc. All Rights Reserved.

#include "Platformer2D3DGameMode.h"
#include "Platformer2D3DCharacter.h"
#include "UObject/ConstructorHelpers.h"

APlatformer2D3DGameMode::APlatformer2D3DGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
