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

	// Keyboard input action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;
	
protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	/** Input handles for axis actions */
	void CameraMove(const FInputActionValue &InputValue);
};