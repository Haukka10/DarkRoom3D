// Fill out your copyright notice in the Description page of Project Settings.


#include "StandForFlashlight.h"

#include "Flashlight.h"
#include "Mirror.h"

// Sets default values
AStandForFlashlight::AStandForFlashlight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStandForFlashlight::BeginPlay()
{
	Super::BeginPlay();
	Range = 1800;
}
AMirror* Mirror = nullptr;
// Called every frame
void AStandForFlashlight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (FlashlightPro != nullptr)
	{
		RayLight();
	}
	else
		if (Mirror != nullptr)
			Mirror->IsHitMirror = false;
}

void AStandForFlashlight::PutDownFlashlight(AFlashlight* Flashlight)
{
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	Flashlight->AttachToComponent(StandGripPoint,AttachmentRules);
	IsFlashlightPut = true;
	FlashlightPro = Flashlight;
	
	if (FlashlightPro->Fuel >= 100)
		FlashlightPro->IsEnabled = true;
}

AFlashlight* AStandForFlashlight::PickUp()
{
	const FDetachmentTransformRules DetachmentRules(EDetachmentRule::KeepWorld,true);
	FlashlightPro->DetachFromActor(DetachmentRules);
	auto c = FlashlightPro;
	IsFlashlightPut = false;
	FlashlightPro = nullptr;
	return c;
}

void AStandForFlashlight::RayLight() const
{
	if (FlashlightPro->IsEnabled == false)
		return;
	
	FHitResult Hits;
	const FVector StartLocation = PointRay->GetComponentLocation();
	const FVector ForwardVector = PointRay->GetForwardVector();
	const FVector EndLocation = StartLocation + (ForwardVector * Range);
	//DrawDebugLine(GetWorld(),StartLocation,EndLocation,FColor::Emerald,false,2,.5,1.5);
	if (GetWorld()->LineTraceSingleByChannel(Hits,StartLocation,EndLocation,ECollisionChannel::ECC_Visibility))
	{
		if (Hits.GetActor()->ActorHasTag("Mirror"))
		{
			Mirror = Cast<AMirror>(Hits.GetActor());
			Mirror->IsHitMirror = true;
			Range = Hits.Distance + 100;
		}
	}
}

