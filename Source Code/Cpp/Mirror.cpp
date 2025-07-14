// Fill out your copyright notice in the Description page of Project Settings.


#include "Mirror.h"

#include "EndMirror.h"
#include "Components/SpotLightComponent.h"

// Sets default values
AMirror::AMirror()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SelfActor = this;
}

// Called when the game starts or when spawned
void AMirror::BeginPlay()
{
	Super::BeginPlay();
	IsHitMirror = false;
}

void AMirror::RayLight()
{
	
	if (Light == nullptr)
		return;
	
	Light->SetIntensity(Intensity);
	for (int i = 0;i < PointsRay.Num();i++)
	{
		const FVector StartLocation = PointsRay[i]->GetComponentLocation();
		const FVector ForwardVector = PointsRay[i]->GetForwardVector();
		const FVector EndLocation = StartLocation + (ForwardVector * MirrorRange);
		auto hit = GetWorld()->LineTraceMultiByChannel(HitsActors,StartLocation,EndLocation,ECollisionChannel::ECC_Visibility);
		//DrawDebugLine(GetWorld(),StartLocation,EndLocation,FColor::Emerald,false,2,.5,10);
		if (hit)
		{
			HitObj(HitsActors);
		}
	}
}

void AMirror::StartReflection()
{
	if (IsHitMirror)
		RayLight();
}

void AMirror::RotationMirror() const
{
	auto c = SelfActor->GetActorRotation();
	SelfActor->SetActorRelativeRotation({c.Pitch, c.Yaw + 90, c.Roll });
}

void AMirror::HitObj(TArray<FHitResult> Objs) const
{
	for (int i = 0;i < Objs.Num();i++)
	{
		auto Actor = Objs[i].GetActor();
		if(Actor->ActorHasTag("Mirror"))
		{
			auto c = Cast<AMirror>(Actor);
			c->IsHitMirror = true;
		}
		if (AEndMirror* End = Cast<AEndMirror>(Actor))
		{
			End->AddMirrorToCheck(SelfActor);
		}
	}
}

// Called every frame
void AMirror::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	StartReflection();
}

