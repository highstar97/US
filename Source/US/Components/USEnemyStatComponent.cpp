#include "Components/USEnemyStatComponent.h"

#include "Characters/Datas/CharacterStat.h"

UUSEnemyStatComponent::UUSEnemyStatComponent()
{
	ExpReward = 0.0f;
}

void UUSEnemyStatComponent::SetExpReward(const float _ExpReward)
{
	ExpReward = _ExpReward;
}

void UUSEnemyStatComponent::LoadStatsAccordingToLevel()
{
	Super::LoadStatsAccordingToLevel();

	FEnemyStat* Stat = DataTable_StatByLevel->FindRow<FEnemyStat>(*FString::FromInt(Level), "");
	if (Stat)
	{
		SetMaxHealth(Stat->MaxHealth);
		SetCurrentHealth(GetMaxHealth());
		SetAttack(Stat->Attack);
		SetDefense(Stat->Defense);
		SetAttackSpeed(Stat->AttackSpeed);
		SetExpReward(Stat->ExpReward);
	}
}