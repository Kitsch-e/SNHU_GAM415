// Copyright Epic Games, Inc. All Rights Reserved.

#include "GAM415GameMode.h"
#include "GAM415Character.h"
#include "UObject/ConstructorHelpers.h"

AGAM415GameMode::AGAM415GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
