// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MainCamera.generated.h"

UCLASS()
class PAPALEADER_API AMainCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMainCamera();


private:
	float CameraRotateDirection;
	float CameraAngle;
	float CameraRotateSpeed;

	float CameraZoomDirection;
	const float CameraZoomSpeed = 800.f;
	const float CameraZoomAngleSpeed = 20.f;
	/** A list of camera zoom lengths and angles to be set **/
	
	std::vector<float> CameraZoomLengths;
	std::vector<float> CameraZoomAngles;
	int CameraZoomIndex;
	int TargetZoomIndex;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// A camera boom component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	
	// A camera component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	// A movement component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UFloatingPawnMovement* MovementComponent;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void RotateCamera(float Direction);

	void ZoomCamera(float Direction);

};
