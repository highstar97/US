#include "Characters/USHeroCharacter.h"

#include "Components/USHeroStatComponent.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AUSHeroCharacter::AUSHeroCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UUSHeroStatComponent>(TEXT("StatComponent")))
{
	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);		// Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 1600.0f;
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

	AttackRepeatedly(DeltaSeconds);
}

void AUSHeroCharacter::AddExp(const float _Exp)
{
	Super::AddExp(_Exp);

	// TODO : this(Character)에 버프 혹은 디버프가 있다면 미리 처리

	UUSHeroStatComponent* HeroStatComponent = Cast<UUSHeroStatComponent>(GetStatComponent());
	if (IsValid(HeroStatComponent))
	{
		HeroStatComponent->AddExp(_Exp);
	}
}

void AUSHeroCharacter::AttackRepeatedly(float DeltaSeconds)
{
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