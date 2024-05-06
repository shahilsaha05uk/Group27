// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePowerup.h"

#include "Components/SphereComponent.h"


ABasePowerup::ABasePowerup()
{
	mCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	mCollider->SetupAttachment(RootComponent);
	mCollider->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapBegin);
	mCollider->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnOverlapEnd);
}

void ABasePowerup::OnOverlapBegin_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}
void ABasePowerup::OnOverlapEnd_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
	
}

void ABasePowerup::ActivatePowerup_Implementation()
{
	
}

void ABasePowerup::DeactivatePowerup_Implementation()
{
	
}
