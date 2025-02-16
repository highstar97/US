#include "Components/USStatComponent.h"

#include "Characters/USCombatCharacter.h"

UUSStatComponent::UUSStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	MaxHealth = 1000.0f;
	CurrentHealth = MaxHealth;
}

void UUSStatComponent::SetMaxHealth(const float _MaxHealth)
{
	MaxHealth = _MaxHealth;
	OnMaxHealthChanged.Broadcast(MaxHealth);
}

void UUSStatComponent::SetCurrentHealth(const float _CurrentHealth)
{
	CurrentHealth = _CurrentHealth;
	OnCurrentHealthChanged.Broadcast(CurrentHealth);
}

void UUSStatComponent::TakeDamage(float DamageAmount)
{
	SetCurrentHealth(FMath::Clamp(CurrentHealth - DamageAmount, 0.0f, CurrentHealth));

	if (CurrentHealth <= KINDA_SMALL_NUMBER)
	{
		OnCharacterDeath.Broadcast();
	}
}

void UUSStatComponent::BeginPlay()
{
	Super::BeginPlay();
}