// Fill out your copyright notice in the Description page of Project Settings.


#include "FuelRegPoints.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Flashlight.h"

// Sets default values
AFuelRegPoints::AFuelRegPoints()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
void AFuelRegPoints::PickUpFuel(AFlashlight* Flashlight) const
{
	Flashlight->AddFuel(RegFuel);
}

// Called when the game starts or when spawned
void AFuelRegPoints::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFuelRegPoints::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

