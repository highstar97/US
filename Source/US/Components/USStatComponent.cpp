#include "Components/USStatComponent.h"

#include "DataValidator.h"
#include "Characters/USCombatCharacter.h"
#include "Characters/Datas/CharacterStat.h"

UUSStatComponent::UUSStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	Level = 1;
	MaxHealth = 0.0f;
	CurrentHealth = MaxHealth;
	Attack = 0.0f;
	Defense = 0.0f;
	AttackSpeed = 0.0f;
}

void UUSStatComponent::SetLevel(const int32 _Level)
{
	Level = _Level;
	OnLevelChanged.Broadcast(Level);
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

void UUSStatComponent::SetAttack(const float _Attack)
{
	Attack = _Attack;
	OnAttackChanged.Broadcast(Attack);
}

void UUSStatComponent::SetDefense(const float _Defense)
{
	Defense = _Defense;
	OnDefenseChanged.Broadcast(Defense);
}

void UUSStatComponent::SetAttackSpeed(const float _AttackSpeed)
{
	AttackSpeed = _AttackSpeed;
	OnAttackSpeedChanged.Broadcast(AttackSpeed);
}

void UUSStatComponent::LoadStatsAccordingToLevel()
{
	if (!IsValid(DataTable_StatByLevel))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s의 Stat Table By Level이 유효하지 않음."), *GetOwner()->GetActorLabel());
		return;
	}
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

	if(!IS_VALID_OR_WARN(DataTable_StatByLevel, FString::Printf(TEXT("%s의 BP에서 DataTable_StatByLevel이 할당되지 않음."), *GetOwner()->GetActorLabel()))) return;
}