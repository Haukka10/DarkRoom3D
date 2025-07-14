// Fill out your copyright notice in the Description page of Project Settings.


#include "EndMirror.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AEndMirror::AEndMirror()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AEndMirror::BeginPlay()
{
	Super::BeginPlay();
	
	if (NextLevel.IsEmpty())
		NextLevel = GetWorld()->GetMapName();

	MirrorHit.Empty();
}

// Called every frame
void AEndMirror::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEndMirror::ChangeLevel() const
{
	if (MirrorHit.Num() >= MaxHitsToOpen)
		OpenDoor();
}

bool AEndMirror::AddMirrorToCheck(AActor* Mirror)
{
	if (MirrorHit.Contains(Mirror))
		return false;
	
	MirrorHit.Add(Mirror);
	ChangeLevel();
	return true;
}

void AEndMirror::OpenDoor() const
{
	UWorld* TheWorld = GetWorld();
	FString CurrentLevel = TheWorld->GetMapName();
	UE_LOG(LogTemp, Error, TEXT("Current Level: %s"), *CurrentLevel);

	UGameplayStatics::OpenLevel(TheWorld, *NextLevel);

	UE_LOG(LogTemp, Error, TEXT("Next Level: %s"), *NextLevel);
}

