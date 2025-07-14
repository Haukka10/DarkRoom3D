// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FuelRegPoints.h"
#include "GameFramework/Actor.h"
#include "RandomSpawnCans.generated.h"

UCLASS()
class ARandomSpawnCans : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARandomSpawnCans();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void SpawnItems();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TMap<AActor*,bool> PointsToSpawn;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	AFuelRegPoints* FuelRegPoints = nullptr;
};
