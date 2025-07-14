// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Flashlight.h"
#include "FuelRegPoints.h"
#include "Mirror.h"
#include "StandForFlashlight.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>("PlayerCamera");
	FirstPersonCameraComponent->SetupAttachment(RootComponent);
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	
}

void APlayerCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	CurrentHalfHeight = Capsule->GetScaledCapsuleHalfHeight();
	GetCharacterMovement()->MaxWalkSpeed = 540.f;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		
		// Cast Ray
		EnhancedInputComponent->BindAction(CastRay, ETriggerEvent::Completed, this, &APlayerCharacter::Castray);

		// Crouching
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Crouch);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::Crouch()
{
	if (!CheckCrouch())
		return;
	
	auto OldPos = FirstPersonCameraComponent->GetRelativeTransform();
	
	if (!bIsCrouching)
	{
		FirstPersonCameraComponent->SetRelativeLocation({FirstPersonCameraComponent->GetRelativeTransform().GetLocation().X, FirstPersonCameraComponent->GetRelativeTransform().GetLocation().Y, OldPos.GetLocation().Z - 30});
		const float NewHeight = CurrentHalfHeight / 2;
		Capsule->SetCapsuleSize(34,NewHeight);
		GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed/2;
		bIsCrouching = true;
	}
	else
	{
		FirstPersonCameraComponent->SetRelativeLocation({FirstPersonCameraComponent->GetRelativeTransform().GetLocation().X, FirstPersonCameraComponent->GetRelativeTransform().GetLocation().Y, OldPos.GetLocation().Z + 30});
		Capsule->SetCapsuleSize(34,CurrentHalfHeight);
		bIsCrouching = false;
		GetCharacterMovement()->MaxWalkSpeed = 520.f;
	}
	
}

bool APlayerCharacter::CheckCrouch() const
{
	FHitResult Hits;
	const FVector StartLocation = FirstPersonCameraComponent->GetComponentLocation();
	const FVector ForwardVector = FirstPersonCameraComponent->GetUpVector();
	const FVector EndLocation = StartLocation + (ForwardVector * 100);
	
	if (auto a = GetWorld()->LineTraceSingleByChannel(Hits,StartLocation,EndLocation,ECollisionChannel::ECC_Visibility))
	{
		if (a)
			return false;
	}
	else
	{
		StartLocation.Rotation().Add(0.f, 11.f, 5.5f);
		const FVector LineEnd = StartLocation + (ForwardVector * 250);
		a = GetWorld()->LineTraceSingleByChannel(Hits,StartLocation,LineEnd,ECollisionChannel::ECC_Visibility);
		
		if (a)
			return false;
	}
	
	return true;
}

void APlayerCharacter::Castray()
{
	FHitResult Hits;

	const FVector StartLocation = FirstPersonCameraComponent->GetComponentLocation();
	const FVector ForwardVector = FirstPersonCameraComponent->GetForwardVector();
	const FVector EndLocation = StartLocation + (ForwardVector * 1000);


	const bool HitActor = GetWorld()->LineTraceSingleByChannel(Hits,StartLocation,EndLocation,ECollisionChannel::ECC_Visibility);
	
	if (HitActor)
	{
		AActor* HitTarget = Hits.GetActor();
		if (HitTarget->ActorHasTag("FuelCan"))
		{
			if (FlashlightItem == nullptr)
				return;
			
			auto c = Cast<AFuelRegPoints>( HitTarget );
			c->PickUpFuel(FlashlightItem);
			c->Destroy();
		}
		if (HitTarget->ActorHasTag("Flashlight"))
		{
			AFlashlight* Aflash = Cast<AFlashlight>(HitTarget);
			Aflash->SetActorEnableCollision(false);
			Aflash->Fuel = 100;
			Aflash->PointLight->SetIntensity(10500.0);
			
			FlashlightItem = Aflash;
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
			FlashlightItem->AttachToComponent(GripPoint, AttachmentRules);
		}
		if (HitTarget->ActorHasTag("Stand"))
		{
			const auto Stand = Cast<AStandForFlashlight>(HitTarget);
			if (Stand->IsFlashlightPut == false)
			{
				if (FlashlightItem == nullptr)
					return;
				
				FDetachmentTransformRules DetachmentRules(EDetachmentRule::KeepWorld,true);
				FlashlightItem->DetachFromActor(DetachmentRules);
				Stand->PutDownFlashlight(FlashlightItem);
				FlashlightItem = nullptr;
			}
			else
			{
				FlashlightItem = Stand->PickUp();
				FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
				FlashlightItem->AttachToComponent(GripPoint, AttachmentRules);
			}
		}
		if (HitTarget->ActorHasTag("Mirror"))
		{
			AMirror* MirrorActor = nullptr;
			MirrorActor = Cast<AMirror>(HitTarget);
			MirrorActor->RotationMirror();
		}
	}
}
