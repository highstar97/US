#include "Components/USStatComponent.h"

#include "GlobalDataConfig.h"
#include "GameInstances/USGameInstance.h"
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
}

void UUSStatComponent::SetDefense(const float _Defense)
{
	Defense = _Defense;
}

void UUSStatComponent::SetAttackSpeed(const float _AttackSpeed)
{
	AttackSpeed = _AttackSpeed;
}

void UUSStatComponent::LoadStatsAccordingToLevel()
{
	if (UWorld* World = GetWorld())
	{
		UUSGameInstance* USGameInstance = Cast<UUSGameInstance>(World->GetGameInstance());
		if (!IsValid(USGameInstance)) return;

		UGlobalDataConfig* CurrenGlobalDataConfig = USGameInstance->GetGlobalDataConfig();
		if (!IsValid(CurrenGlobalDataConfig)) return;

		UDataTable* StatTable = CurrenGlobalDataConfig->GetCharacterStatTable();
		if (IsValid(StatTable))
		{
			FCharacterStat* Stat = StatTable->FindRow<FCharacterStat>(*FString::FromInt(Level), "");
			if (Stat)
			{
				SetMaxHealth(Stat->MaxHealth);
				SetCurrentHealth(GetMaxHealth());
				SetAttack(Stat->Attack);
				SetDefense(Stat->Defense);
				SetAttackSpeed(Stat->AttackSpeed);
			}
		}
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