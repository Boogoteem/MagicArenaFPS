// Fill out your copyright notice in the Description page of Project Settings.

#include "MagicArena.h"
#include "BaseCharacter.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);
    InputComponent->BindAxis("Turn", this, &ABaseCharacter::AddControllerYawInput);
    InputComponent->BindAxis("LookUp", this, &ABaseCharacter::AddControllerPitchInput);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ABaseCharacter::OnStartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &ABaseCharacter::OnStopJump);
}

void ABaseCharacter::MoveRight(float Value) {
	if ((Controller != NULL) && (Value != 0.0f)) {
		if (!((strafeSpeed == 1.0f) || (strafeSpeed == -1.0f))) {
			if (Value < 0) {
				strafeSpeed -= strafeAcc;
				if (strafeSpeed < -1.0f) strafeSpeed = -1.0f;
			}
			else {
				strafeSpeed += strafeAcc;
				if (strafeSpeed > 1.0f) strafeSpeed = 1.0f;
			}
		}
		strafe(strafeSpeed);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("strafeSpeed: ") + FString::SanitizeFloat(strafeSpeed));
	}
	else if (Controller != NULL) {
		if (strafeSpeed != 0.0f) {
			if (strafeSpeed < 0.0f) {
				strafeSpeed += strafeAcc;
				if (strafeSpeed > 0.0f) strafeSpeed = 0.0f;
			}
			else {
				strafeSpeed -= strafeAcc;
				if (strafeSpeed < 0.0f) strafeSpeed = 0.0f;
			}
			if (strafeSpeed != 0) strafe(strafeSpeed);
		}
	}
}

void ABaseCharacter::strafe(float speed) {
	// find out which way is right
	const FRotator Rotation = Controller->GetControlRotation();
	const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
	// add movement in that direction
	AddMovementInput(Direction, speed);
}

void ABaseCharacter::OnStartJump()
{
	bPressedJump = true;
}
void ABaseCharacter::OnStopJump()
{
	bPressedJump = false;
}