#include "USCharacter.h"

#include "Components/USCharacterMovementComponent.h"
#include "Components/USStateComponent.h"
#include "Components/USCharacterAnimationComponent.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PlayerController.h"
#include "Materials/Material.h"
#include "Engine/World.h"

AUSCharacter::AUSCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UUSCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;

	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	StateComponent = CreateDefaultSubobject<UUSStateComponent>(TEXT("State Component"));

	CharacterAnimationComponent = CreateDefaultSubobject<UUSCharacterAnimationComponent>(TEXT("Character Animation Component"));

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AUSCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}
