#include "Components/USHeroStatComponent.h"

#include "Characters/Datas/CharacterStat.h"

UUSHeroStatComponent::UUSHeroStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	CurrentExp = 0.0f;
	ExpToLevelUp = 0.0f;
}

void UUSHeroStatComponent::SetCurrentExp(const float _CurrentExp)
{
	CurrentExp = _CurrentExp;
	OnCurrentExpChanged.Broadcast(CurrentExp);
	while(CurrentExp >= ExpToLevelUp)
	{
		SetCurrentExp(CurrentExp - ExpToLevelUp);
		SetLevel(Level + 1);
	}
}

void UUSHeroStatComponent::SetExpToLevelUp(const float _ExpToLevelUp)
{
	ExpToLevelUp = _ExpToLevelUp;
	OnExpToLevelUpChanged.Broadcast(ExpToLevelUp);
}

void UUSHeroStatComponent::LoadStatsAccordingToLevel()
{
	Super::LoadStatsAccordingToLevel();

	FHeroStat* Stat = DataTable_StatByLevel->FindRow<FHeroStat>(*FString::FromInt(Level), "");
	if (Stat)
	{
		SetMaxHealth(Stat->MaxHealth);
		SetCurrentHealth(GetMaxHealth());
		SetAttack(Stat->Attack);
		SetDefense(Stat->Defense);
		SetAttackSpeed(Stat->AttackSpeed);
		SetExpToLevelUp(Stat->ExpToLevelUp);
	}
}

void UUSHeroStatComponent::AddExp(const float _Exp)
{
	SetCurrentExp(CurrentExp + _Exp);
}