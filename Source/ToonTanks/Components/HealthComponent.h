// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/* --< Includes >-- */
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

/* --< Classes >-- */
class ATankGameModeBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/* --< Constructor >-- */
	UHealthComponent();

protected:
/* --< Functions >-- */
	virtual void BeginPlay() override;

	/* --< UFunctions >-- */
	UFUNCTION()
		void TakeDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

private:
/* --< Pointers >-- */
	AActor* Owner;
	ATankGameModeBase* GameModeRef;
	
/* --< Variables >-- */
	float Health = 0.f;
	
	/* --< UProperties >-- */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
		float DefaultHealth = 100.f;
};
