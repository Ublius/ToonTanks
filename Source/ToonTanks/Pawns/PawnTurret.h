// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/* --< Includes >-- */
#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurret.generated.h"

/* --< Classes >-- */
class APawnTank;

UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()

public:
/* --< Functions >-- */
	virtual void Tick(float DeltaTime) override;

protected:
/* --< Functions >-- */
	virtual void BeginPlay() override;

	// Checks
	virtual void HandleDestruction() override;
	
private:
/* --< Variables >-- */
	FTimerHandle FireRateTimerHandle;
	
	/* --< Pointers >-- */
	APawnTank* PlayerPawn;

	/* --< UProperties >-- */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRate = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRange = 500.0f;
	
/* --< Functions >-- */
	void CheckFireCondition();
	float ReturnDistanceToPlayer();
};
