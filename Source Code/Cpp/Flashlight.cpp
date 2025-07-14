// Fill out your copyright notice in the Description page of Project Settings.


#include "Flashlight.h"

#include "Components/PointLightComponent.h"
#include "Components/SpotLightComponent.h"

// Sets default values
AFlashlight::AFlashlight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFlashlight::BeginPlay()
{
	Super::BeginPlay();
	// check if point light is not a nullptr
	if (PointLight == nullptr)
		UE_LOG(LogTemp, Error, TEXT("PointLight is null"));

	Fuel = MaxFuel;
	NewIntensity = 10000.0;
}

// Called every frame
void AFlashlight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ForceToEnabled)
	{
		ForceLight();
		return;
	}
	
	if (IsEnabled)
		UpdateFuel(DeltaTime);

}

void AFlashlight::AddFuel(float AmountFuel)
{
	float d = (AmountFuel - Fuel) + 10;
	Fuel += d;
}

void AFlashlight::RefreshFuel()
{
	Fuel = MaxFuel;
}

void AFlashlight::UpdateFuel(float DeltaTime)
{
	//consumption fuel
	Fuel -= ConsumptionFuel * DeltaTime;
	ChangePropLight(DeltaTime);
	//check if fuel is less then 0
	if (Fuel <= 0)
	{
		IsEnabled = false;
		PointLight->SetIntensity(0);
	}
}

void AFlashlight::ForceLight() const
{
	PointLight->SetIntensity(NewIntensity);
}

// Change intensity of light
void AFlashlight::ChangePropLight(float DeltaTime)
{
	if (Fuel >= MaxFuel)
	{
		PointLight->SetIntensity(10500.0f);
		return;
	}
	
	NewIntensity -= (ConsumptionFuel * 78.5) * DeltaTime;
	PointLight->SetIntensity(NewIntensity);
}

