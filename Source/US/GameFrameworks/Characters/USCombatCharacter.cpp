#include "USCombatCharacter.h"

#include "Components/USWeaponComponent.h"

AUSCombatCharacter::AUSCombatCharacter()
{
	WeaponComponent = CreateDefaultSubobject<UUSWeaponComponent>(TEXT("WeaponComponent"));
}