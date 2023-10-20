// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCameraController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MainCamera.h"

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
		EnhancedInput->BindAction(RotateAction, ETriggerEvent::Triggered, this, &AMainCameraController::CameraRotateStart);
		EnhancedInput->BindAction(RotateAction, ETriggerEvent::Completed, this, &AMainCameraController::CameraRotateEnd);
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

void AMainCameraController::CameraRotateStart(const FInputActionValue& InputValue)
{
	// Check if the controlled pawn class match with MainCamera class
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		AMainCamera* MainCamera = Cast<AMainCamera>(ControlledPawn);
		if (MainCamera != nullptr)
		{
			// Add rotation to the camera
			MainCamera->RotateCamera(InputValue.Get<float>());
		}
	}
}

void AMainCameraController::CameraRotateEnd()
{
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		AMainCamera* MainCamera = Cast<AMainCamera>(ControlledPawn);
		if (MainCamera != nullptr)
		{
			// Add rotation to the camera
			MainCamera->RotateCamera(0.f);
		}
	}
}




