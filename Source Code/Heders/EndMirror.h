// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndMirror.generated.h"

UCLASS()
class DARKROOM3D_API AEndMirror : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEndMirror();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	bool AddMirrorToCheck(AActor* Mirror);
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<AActor*> Doors;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<AActor*> MirrorHit;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	uint8 MaxHitsToOpen = 0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString NextLevel;
private:

	UFUNCTION()
	void OpenDoor() const;

	UFUNCTION()
	void ChangeLevel() const;
};
