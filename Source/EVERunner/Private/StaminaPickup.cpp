// Fill out your copyright notice in the Description page of Project Settings.


#include "StaminaPickup.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "RootMotionController.h"

AStaminaPickup::AStaminaPickup()
{
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(RootComponent);
	triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger box"));
	triggerBox->SetupAttachment(mesh);
}

void AStaminaPickup::BeginPlay()
{
	Super::BeginPlay();
	triggerBox->OnComponentBeginOverlap.AddDynamic(this, &AStaminaPickup::OnCollisionOverlap);
}

void AStaminaPickup::OnCollisionOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IRootMotionCharacterInterface* character = Cast<IRootMotionCharacterInterface>(OtherActor);
	if (character)
	{
		character->GainStamina(staminaRepplenishAmmount);
		Destroy();
	}
}

