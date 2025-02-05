#include "USCombatCharacter.h"

#include "Controllers/USPlayerController.h"
#include "Components/USCombatComponent.h"
#include "Components/USCharacterAnimationComponent.h"

#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AUSCombatCharacter::AUSCombatCharacter()
{
    CombatComponent = CreateDefaultSubobject<UUSCombatComponent>(TEXT("CombatComponent"));
}

void AUSCombatCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (GetCapsuleComponent())
    {
        if (IsPlayerControlled())
        {
            GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
        }
        else 
        {
            GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
        }
    }
}

void AUSCombatCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    AUSPlayerController* PlayerController = Cast<AUSPlayerController>(GetController());
    if (IsValid(PlayerController))
    {
        UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
        if (IsValid(EnhancedInputComponent) && IsValid(PlayerController->AttackAction))
        {
            EnhancedInputComponent->BindAction(PlayerController->AttackAction, ETriggerEvent::Started, this, &AUSCombatCharacter::Attack);
        }
    }
}

void AUSCombatCharacter::Attack()
{
    if (!IsValid(CombatComponent) || !IsValid(CharacterAnimationComponent)) return;

    if (CombatComponent->CanAttack())
    {
        GetCharacterMovement()->SetMovementMode(MOVE_None);
        CharacterAnimationComponent->PlayAttackMontage();
    }
}