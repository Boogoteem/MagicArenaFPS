// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class MAGICARENA_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	float strafeAcc = 0.2f;
	float strafeSpeed = 0.0f;
	// Sets default values for this character's properties
	ABaseCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//handles strafing
	UFUNCTION()
	void MoveRight(float Val);

	void strafe(float speed);
};
