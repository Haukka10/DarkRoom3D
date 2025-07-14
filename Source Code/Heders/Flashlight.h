// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Flashlight.generated.h"

UCLASS()
class DARKROOM3D_API AFlashlight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlashlight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flashlight|Fuel")
	float Fuel = 0.0F;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flashlight|Fuel")
	float ConsumptionFuel = 0.23F;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flashlight")
	bool IsEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flashlight")
	bool ForceToEnabled = false;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Flashlight")
	class USpotLightComponent* PointLight = nullptr;

	UFUNCTION()
	void AddFuel(float AmountFuel);
	
	UFUNCTION()
	void RefreshFuel();


protected:
	
	UFUNCTION()
	void UpdateFuel(float DeltaTime);
	
	UFUNCTION()
	void ForceLight() const;
	
	UFUNCTION()
	void ChangePropLight(float DeltaTime);

	
private:
	
	float MaxFuel = 100.0F;

	float NewIntensity;
};