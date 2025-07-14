// Fill out your copyright notice in the Description page of Project Settings.


#include "SafeZoneCol.h"

#include "Flashlight.h"
#include "PlayerCharacter.h"

// Sets default values
ASafeZoneCol::ASafeZoneCol()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASafeZoneCol::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ASafeZoneCol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASafeZoneCol::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep)
{
	if (auto Player = Cast<APlayerCharacter>(OtherActor))
	{
		const auto Flashlight = Player->GetFlashlightItem();
		if (Flashlight == nullptr)
			return;

		Flashlight->ForceToEnabled = true;
	}
}

void ASafeZoneCol::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp)
{
	if (auto Player = Cast<APlayerCharacter>(OtherActor))
	{
		const auto Flashlight = Player->GetFlashlightItem();
		if (Flashlight == nullptr)
			return;

		Flashlight->ForceToEnabled = false;
	}
}

