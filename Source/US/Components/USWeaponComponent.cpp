#include "USWeaponComponent.h"

#include "Weapons/USWeapon.h"

UUSWeaponComponent::UUSWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UUSWeaponComponent::EquipWeapon(AUSWeapon* Weapon)
{
	EquippedWeapon = Weapon;
	UE_LOG(LogTemp, Warning, TEXT("Weapon Equipped: %s"), *Weapon->GetName());
}

void UUSWeaponComponent::UseWeapon()
{
    if (EquippedWeapon)
    {
        EquippedWeapon->Attack();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No Weapon Equipped!"));
    }
}

void UUSWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}