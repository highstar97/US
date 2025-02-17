#include "USCombatAnimInstance.h"

#include "Characters/USCombatCharacter.h"
#include "Components/USCombatComponent.h"
#include "Components/USCharacterAnimationComponent.h"

#include "GameFramework/CharacterMovementComponent.h"

UUSCombatAnimInstance::UUSCombatAnimInstance()
{
	bIsInCombat = false;
}

void UUSCombatAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    CombatCharacter = Cast<AUSCombatCharacter>(TryGetPawnOwner());
    if (CombatCharacter.Get())
    {
        CombatComponent = CombatCharacter->GetCombatComponent();
    }
}

void UUSCombatAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    if (!CombatComponent.IsValid()) return;

    bIsInCombat = CombatComponent->GetIsInCombat();
    TOptional<bool> IsWeaponEquippedQureyResult = CombatComponent->GetIsWeaponEquipped();
    if (IsWeaponEquippedQureyResult.IsSet())
    {
        bIsWeaponEquipped = IsWeaponEquippedQureyResult.GetValue();
    }
}

void UUSCombatAnimInstance::AnimNotify_DisableInput()
{
    if (CombatCharacter.Get())
    {
        CombatCharacter->GetCharacterAnimationComponent()->ChangeAttackMontagePriority(EAnimationPriority::UnInterruptedAttack);

        if (APlayerController* PC = Cast<APlayerController>(CombatCharacter->GetController()))
        {
            CombatCharacter->DisableInput(PC);
        }
    }
}

void UUSCombatAnimInstance::AnimNotify_EnableInput()
{
    if (CombatCharacter.Get())
    {
        CombatCharacter->GetCharacterAnimationComponent()->ChangeAttackMontagePriority(EAnimationPriority::Attack);

        if (APlayerController* PC = Cast<APlayerController>(CombatCharacter->GetController()))
        {
            CombatCharacter->EnableInput(PC);
        }
    }
}

void UUSCombatAnimInstance::AnimNotify_CallAttackLogic()
{
    if (!CombatComponent.IsValid()) return;

    CombatComponent->Attack();
}