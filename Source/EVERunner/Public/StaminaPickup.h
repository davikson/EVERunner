// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StaminaPickup.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class EVERUNNER_API AStaminaPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStaminaPickup();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnCollisionOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* triggerBox;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* mesh;

	UPROPERTY(EditDefaultsOnly)
	float staminaRepplenishAmmount = 50;
};
