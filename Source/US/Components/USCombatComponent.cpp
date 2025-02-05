#include "Components/USCombatComponent.h"

#include "Components/USWeaponComponent.h"

UUSCombatComponent::UUSCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	WeaponComponent = CreateDefaultSubobject<UUSWeaponComponent>(TEXT("WeaponComponent"));
}

TOptional<bool> UUSCombatComponent::GetIsWeaponEquipped() const
{
    if (!IsValid(WeaponComponent)) return TOptional<bool>();
    
    if (WeaponComponent->GetEquippedWeapon())
    {
        return TOptional<bool>(true);
    }
    return TOptional<bool>(false);
}

bool UUSCombatComponent::CanAttack() const
{
    TOptional<bool> IsWeaponEquippedQureyResult = GetIsWeaponEquipped();

    if (!IsWeaponEquippedQureyResult.IsSet()) return false;
    if (IsWeaponEquippedQureyResult.GetValue()) return true;
    return false;
}

void UUSCombatComponent::Attack()
{
    TOptional<bool> IsWeaponEquippedQureyResult = GetIsWeaponEquipped();

    if (!IsWeaponEquippedQureyResult.IsSet()) return;

    if (IsWeaponEquippedQureyResult.GetValue())
    {
        EnterCombat();
    }
    WeaponComponent->UseWeapon();
}

void UUSCombatComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UUSCombatComponent::EnterCombat()
{
    UWorld* World = GetWorld();
    if (!World) return;

    if (bIsInCombat)
    {
        UE_LOG(LogTemp, Warning, TEXT("Combat Extended"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Combat Started"));
        bIsInCombat = true;
    }

    ResetCombatTimer();
}

void UUSCombatComponent::ExitCombat()
{
    if (!bIsInCombat) return;

    UE_LOG(LogTemp, Warning, TEXT("Combat Ended"));
    bIsInCombat = false;
}

void UUSCombatComponent::ResetCombatTimer()
{
    UWorld* World = GetWorld();
    if (!World) return;

    World->GetTimerManager().ClearTimer(CombatTimerHandle);
    World->GetTimerManager().SetTimer(CombatTimerHandle, this, &UUSCombatComponent::ExitCombat, CombatTimeoutDuration, false);
}