// Fill out your copyright notice in the Description page of Project Settings.


#include "Killer.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "RootMotionController.h"
#include "LevelController.h"

AKiller::AKiller()
{
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(RootComponent);
	triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger box"));
	triggerBox->SetupAttachment(mesh);
}

void AKiller::BeginPlay()
{
	Super::BeginPlay();
	triggerBox->OnComponentBeginOverlap.AddDynamic(this, &AKiller::OnCollisionOverlap);
#ifdef WITH_EDITOR
	if (!levelController) UE_LOG(LogTemp, Error, TEXT("levelController pointer not set for AKiller(%s)"), *GetName());
#endif

}

void AKiller::OnCollisionOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<IRootMotionCharacterInterface>(OtherActor))
	{
		if (levelController) levelController->PlayerKilled();
	}
}

