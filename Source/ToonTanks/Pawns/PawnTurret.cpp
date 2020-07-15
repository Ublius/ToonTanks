// Fill out your copyright notice in the Description page of Project Settings.

/* --< Includes >-- */
#include "PawnTurret.h"
#include "PawnTank.h"
#include "Kismet/GameplayStatics.h"

/* --< Functions >-- */
void APawnTurret::BeginPlay()
{
    Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true, false);
    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(!PlayerPawn || ReturnDistanceToPlayer() > FireRange)
        return;

    RotateTurret(PlayerPawn->GetActorLocation());
}

    /* --< Handles >-- */
void APawnTurret::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}

void APawnTurret::CheckFireCondition()
{
    // If player == null || is dead then bail
    if(!PlayerPawn || PlayerPawn->GetPlayerAlive())
        return;
    
    // if Player, Player IS in range Then Fire
    if(ReturnDistanceToPlayer() <= FireRange)
        Fire();
}

float APawnTurret::ReturnDistanceToPlayer()
{
    // Check if we have a valid reference to player
    if (!PlayerPawn)
        return 0.0f;

    float Distance = (PlayerPawn->GetActorLocation() - GetActorLocation()).Size();
    return Distance;
} 