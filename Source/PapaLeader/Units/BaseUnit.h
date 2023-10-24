// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseUnit.generated.h"

UCLASS()
class PAPALEADER_API ABaseUnit : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseUnit();

	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Blueprint editable properties **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = unitProperty, meta = (AllowPrivateAccess = "true"))
	float MovingSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = unitProperty, meta = (AllowPrivateAccess = "true"))
	float CapsuleRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = unitProperty, meta = (AllowPrivateAccess = "true"))
	float CapsuleHeight;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
