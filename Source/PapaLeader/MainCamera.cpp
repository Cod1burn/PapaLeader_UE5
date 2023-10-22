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
	CameraZoomLengths = { 600.f, 1000.f, 1400.f, 1800.f, 2200.f };
	CameraZoomAngles = { -30.f, -45.f, -60.f, -60.f, -70.f };
	CameraZoomIndex = 2;
	TargetZoomIndex = CameraZoomIndex;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->TargetArmLength = CameraZoomLengths[CameraZoomIndex];
	CameraBoom->SetRelativeRotation(FRotator(CameraZoomAngles[CameraZoomIndex], 0.f, 0.f));
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
	if (CameraRotateDirection != 0.f)
	{
		FRotator Rotator = CameraBoom->GetRelativeRotation();
		Rotator.Yaw += DeltaTime * CameraRotateDirection * CameraRotateSpeed;
		CameraBoom->SetRelativeRotation(Rotator);
	}

	// Zoom in or out the camera boom smoothly
	if (CameraZoomIndex != TargetZoomIndex)
	{
		CameraBoom->TargetArmLength = TargetZoomIndex > CameraZoomIndex ? FMath::Min(CameraBoom->TargetArmLength + DeltaTime * CameraZoomSpeed, CameraZoomLengths[TargetZoomIndex])
		: FMath::Max(CameraBoom->TargetArmLength - DeltaTime * CameraZoomSpeed, CameraZoomLengths[TargetZoomIndex]);
		FRotator Rotator = CameraBoom->GetRelativeRotation();
		Rotator.Pitch = TargetZoomIndex > CameraZoomIndex ? FMath::Max(Rotator.Pitch + DeltaTime * CameraZoomAngleSpeed, CameraZoomAngles[TargetZoomIndex])
		: FMath::Min(Rotator.Pitch - DeltaTime * CameraZoomAngleSpeed, CameraZoomAngles[TargetZoomIndex]);
		CameraBoom->SetRelativeRotation(Rotator);
		if (CameraBoom->TargetArmLength == CameraZoomLengths[TargetZoomIndex] && Rotator.Pitch == CameraZoomAngles[TargetZoomIndex])
		{
			CameraZoomIndex = TargetZoomIndex;
		}
	}
}

void AMainCamera::RotateCamera(float Direction)
{
	CameraRotateDirection = Direction;
}

void AMainCamera::ZoomCamera(float Direction)
{
	if (Direction > 0.f)
	{
		if (TargetZoomIndex <= CameraZoomIndex && CameraZoomIndex < CameraZoomLengths.size() - 1)
		{
			TargetZoomIndex += 1;
			UE_LOG(LogTemp, Display, TEXT("TargetZoomIndex: %d, CameraZoomIndex: %d"), TargetZoomIndex, CameraZoomIndex);
		}
	}
	else if (Direction < 0.f)
	{
		if (TargetZoomIndex >= CameraZoomIndex && CameraZoomIndex > 0)
		{
			TargetZoomIndex -= 1;
			UE_LOG(LogTemp, Display, TEXT("TargetZoomIndex: %d, CameraZoomIndex: %d"), TargetZoomIndex, CameraZoomIndex);
		}
	}
}


