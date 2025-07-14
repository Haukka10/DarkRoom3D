// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomSpawnCans.h"

#include "FuelRegPoints.h"

// Sets default values
ARandomSpawnCans::ARandomSpawnCans()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARandomSpawnCans::BeginPlay()
{
	Super::BeginPlay();

	if (FuelRegPoints == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("FuelRegPoints is null"));
		return;
	}
	SpawnItems();
}

void ARandomSpawnCans::SpawnItems()
{
	for (auto [Item,IsSpawn] : PointsToSpawn)
	{
		if (IsSpawn == false)
		{
			FTransform SpawnTransform = Item->GetTransform();
			FActorSpawnParameters SpawnParameters;
			UWorld* World = GetWorld();
			auto c = World->SpawnActor(FuelRegPoints->GetClass(),&SpawnTransform,SpawnParameters);
			IsSpawn = true;
		}
	}
}

// Called every frame
void ARandomSpawnCans::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

