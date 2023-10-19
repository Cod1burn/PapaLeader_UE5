// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCameraController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AMainCameraController::AMainCameraController()
{
	// Set this controller to be the pawn's input controller
	bAutoManageActiveCameraTarget = false;
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void AMainCameraController::BeginPlay()
{
	Super::BeginPlay();
	// Add mapping context to the local player
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(MappingContext, 0);
	}
}

void AMainCameraController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// Set up axis bindings
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCameraController::CameraMove);
		UE_LOG(LogTemp, Display, TEXT("Binding MoveAction to CameraMove"));
	}
}

void AMainCameraController::CameraMove(const FInputActionValue &InputValue)
{
	// Add Movement to the pawn by 2d value in input action
	FVector2D Movement = InputValue.Get<FVector2d>();
	// print out the movement value
	
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		ControlledPawn->AddMovementInput(FVector(Movement.X, Movement.Y, 0.f));
	}
}




