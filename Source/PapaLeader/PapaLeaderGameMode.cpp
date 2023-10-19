// Copyright Epic Games, Inc. All Rights Reserved.

#include "PapaLeaderGameMode.h"
#include "PapaLeaderPlayerController.h"
#include "PapaLeaderCharacter.h"
#include "UObject/ConstructorHelpers.h"

APapaLeaderGameMode::APapaLeaderGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = APapaLeaderPlayerController::StaticClass();

	// Do not set a default pawn class
	static ConstructorHelpers::FClassFinder<ACharacter> DefaultPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if(DefaultPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = DefaultPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
		UE_LOG(LogTemp, Warning, TEXT("PlayerControllerClass: %s"), *PlayerControllerClass->GetName());
	}
}