#include "Components/USCombatComponent.h"

#include "Characters/USCombatCharacter.h"
#include "Components/USWeaponComponent.h"
#include "Weapons/USWeapon.h"

UUSCombatComponent::UUSCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	WeaponComponent = CreateDefaultSubobject<UUSWeaponComponent>(TEXT("WeaponComponent"));
}

AUSWeapon* UUSCombatComponent::GetEquippedWeapon() const
{
    if (!IsValid(WeaponComponent))
    {
        UE_LOG(LogTemp, Error, TEXT("%s의 Weapon Component가 유효하지 않음."), *GetOwner()->GetActorLabel());
        return nullptr;
    }

    AUSWeapon* EquippedWeapon = WeaponComponent->GetEquippedWeapon();
    if (IsValid(EquippedWeapon))
    {
        return EquippedWeapon;
    }
    else return nullptr;
}

bool UUSCombatComponent::Attack()
{
    AUSWeapon* EquippedWeapon = GetEquippedWeapon();
    if (!IsValid(EquippedWeapon)) return false;

    AUSCombatCharacter* CombatCharacter = Cast<AUSCombatCharacter>(GetOwner());
    if (!IsValid(CombatCharacter)) return false;
    
    EquippedWeapon->Attack();
    if (CombatCharacter->IsPlayerControlled())
    {
        EnterCombat();
    }
    return true;
}

void UUSCombatComponent::EnterCombat()
{
    if (!bIsInCombat)
    {
        bIsInCombat = true;
    }

    ResetCombatTimer();
}

void UUSCombatComponent::ExitCombat()
{
    if (!bIsInCombat) return;

    bIsInCombat = false;
}

void UUSCombatComponent::ResetCombatTimer()
{
    UWorld* World = GetWorld();
    if (!World) return;

    World->GetTimerManager().ClearTimer(CombatTimerHandle);
    World->GetTimerManager().SetTimer(CombatTimerHandle, this, &UUSCombatComponent::ExitCombat, CombatTimeoutThreshold, false);
}