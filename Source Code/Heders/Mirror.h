// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/SpotLight.h"
#include "GameFramework/Actor.h"
#include "Mirror.generated.h"

UCLASS()
class DARKROOM3D_API AMirror : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMirror();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	mutable AActor* SelfActor;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<FHitResult> HitsActors;

	UFUNCTION()
	void RotationMirror() const;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void RayLight();

	UFUNCTION()
	void StartReflection();

	UFUNCTION()
	void HitObj(TArray<FHitResult> Objs) const;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<UMeshComponent*> PointsRay;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USpotLightComponent* Light = nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Intensity = 10000.0F;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MirrorRange = 478.0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool IsHitMirror;
};
