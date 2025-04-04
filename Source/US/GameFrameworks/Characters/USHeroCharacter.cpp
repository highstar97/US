#include "Characters/USHeroCharacter.h"

#include "Components/USStatComponent.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AUSHeroCharacter::AUSHeroCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);		// Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;							// Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;		// Camera does not rotate relative to arm

	AttackElapsed = 0.0f;

	GetCharacterMovement()->MaxWalkSpeed = 300.0f;

	PrimaryActorTick.bCanEverTick = true;
}

void AUSHeroCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	float AttackSpeed = GetStatComponent()->GetAttackSpeed();
	if (AttackSpeed <= 0.0f) return;

	float AttackInterval = (1.0f / AttackSpeed);

	AttackElapsed += DeltaSeconds;
	if (AttackElapsed >= AttackInterval)
	{
		AttackElapsed -= AttackInterval;
		Attack();
	}
}