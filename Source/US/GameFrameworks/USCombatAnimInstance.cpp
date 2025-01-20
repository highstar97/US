#include "USCombatAnimInstance.h"

#include "Characters/USCombatCharacter.h"
#include "Components/USCombatComponent.h"

UUSCombatAnimInstance::UUSCombatAnimInstance()
{
	bIsInCombat = false;
}

void UUSCombatAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    AUSCombatCharacter* OwnerCharacter = Cast<AUSCombatCharacter>(TryGetPawnOwner());
    if (IsValid(OwnerCharacter))
    {
        CombatComponent = OwnerCharacter->GetCombatComponent();
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