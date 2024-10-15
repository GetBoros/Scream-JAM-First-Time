// Copyright Epic Games, Inc. All Rights Reserved.

#include "JamScreamGameMode.h"
#include "JamScreamCharacter.h"
#include "UObject/ConstructorHelpers.h"

AJamScreamGameMode::AJamScreamGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
