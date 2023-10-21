// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "MainCameraController.generated.h"

/**
 * 
 */
UCLASS()
class PAPALEADER_API AMainCameraController : public APlayerController
{
	GENERATED_BODY()

public:
	AMainCameraController();
	
	// Mapping context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* MappingContext;

	/** Keyboard input actions **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* RotateAction;

	/** Mouse input actions **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* ZoomAction;

	
protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaSeconds) override;

	void CameraMove(const FVector2d &Direction);

	/** Input handles for axis actions */
	void KeyboardCameraMove(const FInputActionValue &InputValue);

	void CameraRotateStart(const FInputActionValue &InputValue);

	void CameraRotateEnd();

	/** Input handles for mouse actions */
	/**
	 * Called by each frame to detect if the mouse cursor is inside the viewport
	 * If the mouse is at the edge of the viewport, move the camera in that direction.
	 */
	void MouseCameraMove();

	void CameraZoomStart(const FInputActionValue &InputValue);
};
