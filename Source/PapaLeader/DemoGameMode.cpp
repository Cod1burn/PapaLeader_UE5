// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoGameMode.h"

#include "MainCamera.h"
#include "MainCameraController.h"

ADemoGameMode::ADemoGameMode()
{
	// Set Controller class to be the blueprint controller
	static ConstructorHelpers::FClassFinder<APlayerController> ControllerBP(TEXT("/Game/TopDown/Blueprints/BP_MainCameraController"));
	if(ControllerBP.Class != NULL)
	{
		PlayerControllerClass = ControllerBP.Class;
		UE_LOG(LogTemp, Warning, TEXT("PlayerControllerClass: %s"), *PlayerControllerClass->GetName());
	}
	
	static ConstructorHelpers::FClassFinder<APawn> PawnBP(TEXT("/Game/TopDown/Blueprints/BP_MainCamera"));
	if(PawnBP.Class != NULL)
	{
		DefaultPawnClass = PawnBP.Class;
		UE_LOG(LogTemp, Warning, TEXT("DefaultPawnClass: %s"), *DefaultPawnClass->GetName());
	}
}
