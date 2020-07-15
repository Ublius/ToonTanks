// Fill out your copyright notice in the Description page of Project Settings.

/* --< Includes >-- */
#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

/* --< Constructor >-- */
APawnTank::APawnTank()
{
    
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Srping Arm"));
    SpringArm->SetupAttachment(RootComponent);
    
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

/* --< Functions >-- */
void APawnTank::BeginPlay()
{
    Super::BeginPlay();

    PlayerControllerRef = Cast<APlayerController>(GetController());
}

void APawnTank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    Rotate();
    Move();

    if (PlayerControllerRef)
    {
        PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
        FVector HitLocation = TraceHitResult.ImpactPoint;

        RotateTurret(HitLocation);
    }
}

void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

        /* --< Movement >-- */
    PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
    PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateInput);

        /* --< Actions >-- */
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);
}

    /* --< Getters >-- */
bool APawnTank::GetPlayerAlive()
{
    return bDead;
}

    /* --< Handles >-- */
void APawnTank::HandleDestruction()
{
    Super::HandleDestruction();

    bDead = true;

    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
}

    /* --< Calculations >-- */
void APawnTank::CalculateMoveInput(const float Value)
{
    MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
}

void APawnTank::CalculateRotateInput(const float Value)
{
    const float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
    const FRotator Rotation = FRotator(0, RotateAmount, 0);
    RotationDirection = FQuat(Rotation);
}

    /* --< Movement >-- */
void APawnTank::Move()
{
    AddActorLocalOffset(MoveDirection, true);
}

void APawnTank::Rotate()
{
    AddActorLocalRotation(RotationDirection, true);
}
