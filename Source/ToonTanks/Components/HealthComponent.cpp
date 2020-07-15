// Fill out your copyright notice in the Description page of Project Settings.

/* --< Includes >-- */
#include "HealthComponent.h"
#include "ToonTanks/GameModes/TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"

/* --< Constructor >-- */
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = DefaultHealth;
	
	GameModeRef = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	Owner = GetOwner();
	if(Owner)
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	else
		UE_LOG(LogTemp, Warning, TEXT("Health Component has no referecne to the Owner"));
}

/* --< Functions >-- */
void UHealthComponent::TakeDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	if(Damage == 0 || Health == 0)
		return;

	Health = FMath::Clamp(Health - Damage, 0.f, DefaultHealth);
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);
	
	if(Health <= 0)
	{
		if(GameModeRef)
			GameModeRef->ActorDied(Owner);
		else
			UE_LOG(LogTemp, Warning, TEXT("Health Component has no referecne to the GameMode"));
	}
}
