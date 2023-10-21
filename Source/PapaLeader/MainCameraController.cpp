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
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCameraController::KeyboardCameraMove);
		EnhancedInput->BindAction(RotateAction, ETriggerEvent::Triggered, this, &AMainCameraController::CameraRotateStart);
		EnhancedInput->BindAction(RotateAction, ETriggerEvent::Completed, this, &AMainCameraController::CameraRotateEnd);
		EnhancedInput->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &AMainCameraController::CameraZoomStart);
		UE_LOG(LogTemp, Display, TEXT("Binding MoveAction to CameraMove"));
	}
}

void AMainCameraController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	MouseCameraMove();
}

void AMainCameraController::CameraMove(const FVector2d &Direction)
{
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		/** Move the pawn by the pawn facing direction **/
		// Erase the Z component of the forward direction
		FVector3d ForwardDirection = ControlledPawn->GetActorForwardVector();
		ForwardDirection.Z = 0.f;
		ForwardDirection.Normalize();
		ControlledPawn->AddMovementInput(ForwardDirection, Direction.Y);
		ControlledPawn->AddMovementInput(ControlledPawn->GetActorRightVector(), Direction.X);
	}
}

void AMainCameraController::KeyboardCameraMove(const FInputActionValue &InputValue)
{
	// Add Movement to the pawn by 2d value in input action
	FVector2D Movement = InputValue.Get<FVector2d>();
	CameraMove(Movement);
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

void AMainCameraController::MouseCameraMove()
{
	// Get Mouse cursor position
	FVector2d MousePosition;
	GetMousePosition(MousePosition.X, MousePosition.Y);
	
	// Get viewport size
	int ViewportWidth, ViewportHeight;
	const float BufferRatio = 0.05f;
	GetViewportSize(ViewportWidth, ViewportHeight);
	
	// Set a buffer zone for the mouse to control the camera speed
	float BufferX = ViewportWidth * BufferRatio;
	float BufferY = ViewportHeight * BufferRatio;

	// Check if the mouse is at the edge of the viewport
	FVector2d Direction = FVector2d::ZeroVector;

	// The closer mouse cursor to the edge of the viewport, the faster the camera moves
	if (MousePosition.X <= BufferX)
		Direction.X = -1.f * (BufferX - MousePosition.X) / BufferX;
	else if (MousePosition.X >= ViewportWidth - BufferX)
		Direction.X = 1.f * (MousePosition.X - ViewportWidth + BufferX) / BufferX;
	
	if (MousePosition.Y <= BufferY)
		Direction.Y = 1.f * (BufferY - MousePosition.Y) / BufferY;
	else if (MousePosition.Y >= ViewportHeight - BufferY)
		Direction.Y = -1.f * (MousePosition.Y - ViewportHeight + BufferY) / BufferY;
	
	CameraMove(Direction);
}

void AMainCameraController::CameraZoomStart(const FInputActionValue& InputValue)
{
	float ZoomDirection = InputValue.Get<float>();
	if (AMainCamera* MainCamera = CastChecked<AMainCamera>(GetPawn()))
	{
		MainCamera->ZoomCamera(ZoomDirection);
	}
}




