#include "USCombatCharacter.h"

#include "Controllers/USPlayerController.h"
#include "Components/USCombatComponent.h"

#include "EnhancedInputComponent.h"

AUSCombatCharacter::AUSCombatCharacter()
{
    CombatComponent = CreateDefaultSubobject<UUSCombatComponent>(TEXT("CombatComponent"));
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
    if (IsValid(CombatComponent))
    {
        CombatComponent->Attack();
    }
}