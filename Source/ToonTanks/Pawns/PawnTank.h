// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/* --< Includes >-- */
#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTank.generated.h"

/* --< Classes >-- */
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TOONTANKS_API APawnTank : public APawnBase
{
	GENERATED_BODY()

public:
/* --< Constructor >-- */
	APawnTank();

/* --< Functions >-- */
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/* --< Getters >-- */
	bool GetPlayerAlive();
	
protected:
/* --< Functions >-- */
	virtual void BeginPlay() override;

	// Checks
	virtual  void HandleDestruction() override;

private:
/* --< Pointers >-- */
	APlayerController* PlayerControllerRef;
	
	/* --< UProperties >-- */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UCameraComponent* Camera;
	
/* --< Variables >-- */
	FVector MoveDirection;
	FQuat RotationDirection;
	FHitResult TraceHitResult;
	bool bDead = false;
	
	/* --< UProperties >-- */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MoveSpeed = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float RotateSpeed = 100.0f;
	
/* --< Functions >-- */
	/* --< Calculations >-- */
	void CalculateMoveInput(float Value);
	void CalculateRotateInput(float Value);

	/* --< Movement >-- */
	void Move();
	void Rotate();
};
