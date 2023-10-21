// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCamera.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMainCamera::AMainCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Set up camera boom and set it to be the root component
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->TargetArmLength = 1400.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level
	SetRootComponent(CameraBoom);
	RootComponent->SetMobility(EComponentMobility::Movable);

	CameraZoomDirection = 0.f;

	// Set up camera component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	// Set up movement component
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	// Print out the movement speed
	UE_LOG(LogTemp, Display, TEXT("Movement Speed: %f"), MovementComponent->MaxSpeed);
	

}

// Called when the game starts or when spawned
void AMainCamera::BeginPlay()
{
	Super::BeginPlay();
	CameraRotateDirection = 0.f;
	CameraAngle = 0.f;
	CameraRotateSpeed = 100.f;
	
}

// Called every frame
void AMainCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Rotate the camera boom horizontally
	CameraAngle += DeltaTime * CameraRotateDirection * CameraRotateSpeed;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, CameraAngle, 0.f));

	// Zoom in or out the camera by changing the camera boom length
	if (CameraZoomDirection != 0.f)
	{
		CameraBoom->TargetArmLength += DeltaTime * CameraZoomDirection * CameraZoomSpeed;
		
		if (CameraBoom->TargetArmLength > CameraBoomMaxLength)
			CameraBoom->TargetArmLength = CameraBoomMaxLength;
		else if (CameraBoom->TargetArmLength < CameraBoomMinLength)
			CameraBoom->TargetArmLength = CameraBoomMinLength;
	}
}

void AMainCamera::RotateCamera(float Direction)
{
	CameraRotateDirection = Direction;
}

void AMainCamera::ZoomCamera(float Direction)
{
	CameraZoomDirection = Direction;
}


