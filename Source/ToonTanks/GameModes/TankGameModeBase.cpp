// Fill out your copyright notice in the Description page of Project Settings.

/* --< Includes >-- */
#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"

void ATankGameModeBase::BeginPlay()
{
    TargetTurrets = GetTargetTurretCount();
    
    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
    PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
    
    HandleGameStart();
    Super::BeginPlay();
}

/* --< Functions >-- */
    /* --< Handles >-- */
void ATankGameModeBase::HandleGameStart()
{
   GameStart();
    if(PlayerControllerRef)
    {
        PlayerControllerRef->SetPlayerEnableState(false);

        FTimerHandle PlayerEnableHandle;
        FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::SetPlayerEnableState, true);
        GetWorldTimerManager().SetTimer(OUT PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
    }
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
  GameOver(PlayerWon);
}

    /* --< Getters >-- */
int32 ATankGameModeBase::GetTargetTurretCount()
{
    TSubclassOf<APawnTurret> ClassToFind = APawnTurret::StaticClass();
    TArray<AActor*> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, TurretActors);
    return TargetTurrets = TurretActors.Num();
}

    /* --< Actions >-- */
void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
    if(DeadActor == PlayerTank)
    {
        PlayerTank->PawnDestroyed();
        HandleGameOver(false);

        if(PlayerControllerRef)
            PlayerControllerRef->SetPlayerEnableState(false);
    }
    else if(APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
    {
        DestroyedTurret->PawnDestroyed();
        TargetTurrets--;

        if(TargetTurrets == 0)
            HandleGameOver(true);
    }
}