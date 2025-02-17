#include "Components/USStatComponent.h"

#include "GameDataConfig.h"
#include "GameStates/USGameState.h"
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

void UUSStatComponent::LoadStatsAccordingToLevel()
{
	if (UWorld* World = GetWorld())
	{
		AUSGameState* GameState = World->GetGameState<AUSGameState>();
		if (!IsValid(GameState)) return;

		UGameDataConfig* CurrentGameDataConfig = GameState->GetCurrentGameDataConfig();
		if (!IsValid(CurrentGameDataConfig)) return;

		UDataTable* StatTable = CurrentGameDataConfig->GetCharacterStatTable();
		if (IsValid(StatTable))
		{
			FCharacterStat* Stat = StatTable->FindRow<FCharacterStat>(*FString::FromInt(Level), "");
			if (Stat)
			{
				SetMaxHealth(Stat->MaxHealth);
				SetCurrentHealth(GetMaxHealth());
				SetAttack(Stat->Attack);
				SetDefense(Stat->Defense);
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

void UUSStatComponent::BeginPlay()
{
	Super::BeginPlay();
}