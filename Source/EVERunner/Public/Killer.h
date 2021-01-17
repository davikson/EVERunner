// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Killer.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class ALevelController;

UCLASS()
class EVERUNNER_API AKiller : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKiller();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnCollisionOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* triggerBox;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* mesh;

	UPROPERTY(EditInstanceOnly, Category = "Params")
	ALevelController* levelController;
};
