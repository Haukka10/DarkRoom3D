// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Flashlight.h"
#include "GameFramework/Actor.h"
#include "StandForFlashlight.generated.h"


UCLASS()
class DARKROOM3D_API AStandForFlashlight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStandForFlashlight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PutDownFlashlight(AFlashlight* Flashlight);

	UPROPERTY()
	mutable bool IsFlashlightPut = false;

	AFlashlight* PickUp();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UMeshComponent* StandGripPoint = nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UMeshComponent* PointRay = nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	AFlashlight* FlashlightPro = nullptr;

private:
	void RayLight() const;

	UPROPERTY()
	mutable float Range = 1800;

};
