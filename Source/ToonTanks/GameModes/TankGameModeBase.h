// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/* --< Includes >-- */
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

/* --< Classes >-- */
class APawnTank;
class APawnTurret;
class APlayerControllerBase;

UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
/* --< Functions >-- */
	void ActorDied(AActor* DeadActor);

	/* --< UFunctions >-- */
	UFUNCTION(BlueprintImplementableEvent)
		void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
		void GameOver(bool PlayerWon);

protected:
/* --< Functions >-- */
	virtual void BeginPlay() override;

private:
/* --< Pointers >-- */
	APlayerControllerBase* PlayerControllerRef;
	
	/* --< UProperties >-- */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
		APawnTank* PlayerTank;

/* --< Variables >-- */
	int32 TargetTurrets = 0;

	/* --< UProperties >-- */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game", meta = (AllowPrivateAccess = "true"))
		int StartDelay = 4;
	
/* --< Functions >-- */
	/* --< Handles >-- */
	void HandleGameStart();
	void HandleGameOver(bool PayerWon);

	/* --< Getters >-- */
	int32 GetTargetTurretCount();
};
