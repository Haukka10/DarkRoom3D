// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FuelRegPoints.generated.h"

class AFlashlight;

UCLASS()
class DARKROOM3D_API AFuelRegPoints : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFuelRegPoints();

	UPROPERTY(EditAnywhere)
	float RegFuel = 100;

	UFUNCTION()
	void PickUpFuel(AFlashlight* Flashlight) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
