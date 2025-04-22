#include "UI/StatWidget.h"

#include "DataValidator.h"
#include "Components/USHeroStatComponent.h"

#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UStatWidget::BindCharacterStat(UUSStatComponent* _StatComponent)
{
	if (!IS_VALID_OR_WARN(_StatComponent, TEXT("StatWidget에 StatComponent가 제대로 할당되지 않음."))) return;

    UUSHeroStatComponent* _HeroStatComponent = Cast<UUSHeroStatComponent>(_StatComponent);
    if (!_HeroStatComponent) return;

    HeroStatComponent = _HeroStatComponent;
    HeroStatComponent->OnLevelChanged.AddDynamic(this, &UStatWidget::UpdateTextBlock_Level);
    HeroStatComponent->OnMaxHealthChanged.AddDynamic(this, &UStatWidget::UpdateProgressBar_Health);
    HeroStatComponent->OnCurrentHealthChanged.AddDynamic(this, &UStatWidget::UpdateProgressBar_Health);
    HeroStatComponent->OnAttackChanged.AddDynamic(this, &UStatWidget::UpdateTextBlock_Attack);
    HeroStatComponent->OnDefenseChanged.AddDynamic(this, &UStatWidget::UpdateTextBlock_Defense);
    HeroStatComponent->OnAttackSpeedChanged.AddDynamic(this, &UStatWidget::UpdateTextBlock_AttackSpeed);
    HeroStatComponent->OnExpToLevelUpChanged.AddDynamic(this, &UStatWidget::UpdateProgressBar_Experience);
    HeroStatComponent->OnCurrentExpChanged.AddDynamic(this, &UStatWidget::UpdateProgressBar_Experience);

    UpdateTextBlock_Name();
    UpdateTextBlock_Level(HeroStatComponent->GetLevel());
    UpdateProgressBar_Health(HeroStatComponent->GetMaxHealth());
    UpdateTextBlock_Attack(HeroStatComponent->GetAttack());
    UpdateTextBlock_Defense(HeroStatComponent->GetDefense());
    UpdateTextBlock_AttackSpeed(HeroStatComponent->GetAttackSpeed());
}

void UStatWidget::UpdateTextBlock_Name()
{
    
}

void UStatWidget::UpdateTextBlock_Level(int32 _Level)
{
    if (!IsValid(TextBlock_Level) || !HeroStatComponent.IsValid()) return;

    if (_Level <= 0) return;

    TextBlock_Level->SetText(FText::FromString(FString::FromInt(_Level)));
}

void UStatWidget::UpdateTextBlock_Attack(float _Attack)
{
    if (!IsValid(TextBlock_Attack) || !HeroStatComponent.IsValid()) return;

    if (_Attack < 0) return;

    TextBlock_Attack->SetText(FText::FromString(FString::SanitizeFloat(_Attack)));
}

void UStatWidget::UpdateTextBlock_Defense(float _Defense)
{
    if (!IsValid(TextBlock_Defense) || !HeroStatComponent.IsValid()) return;

    if (_Defense < 0) return;

    TextBlock_Defense->SetText(FText::FromString(FString::SanitizeFloat(_Defense)));
}

void UStatWidget::UpdateTextBlock_AttackSpeed(float _AttackSpeed)
{
    if (!IsValid(TextBlock_AttackSpeed) || !HeroStatComponent.IsValid()) return;

    if (_AttackSpeed < 0) return;

    TextBlock_AttackSpeed->SetText(FText::FromString(FString::SanitizeFloat(_AttackSpeed)));
}

void UStatWidget::UpdateTextBlock_Health(const float _CurrentHealth, const float _MaxHealth)
{
    if (!IsValid(TextBlock_Health)) return;

    TextBlock_Health->SetText(FText::FromString(FString::Printf(TEXT("%.2f / %.2f"), _CurrentHealth, _MaxHealth)));
}

void UStatWidget::UpdateTextBlock_Experience(const float _CurrentExp, const float _ExpToLevelUp)
{
    if (!IsValid(TextBlock_Experience)) return;

    TextBlock_Experience->SetText(FText::FromString(FString::Printf(TEXT("%.2f / %.2f"), _CurrentExp, _ExpToLevelUp)));
}

void UStatWidget::UpdateProgressBar_Health(float _ChangedStat)
{
    if (!IsValid(ProgressBar_Health) || !HeroStatComponent.IsValid()) return;

    if (HeroStatComponent->GetMaxHealth() == 0.0f) return;
    
    float CurrentHealth = HeroStatComponent.Get()->GetCurrentHealth();
    float MaxHealth = HeroStatComponent->GetMaxHealth();
    UpdateTextBlock_Health(CurrentHealth, MaxHealth);

    float HealthRatio = FMath::Clamp(CurrentHealth / MaxHealth, 0.0f, 1.0f);
    ProgressBar_Health->SetPercent(HealthRatio);
}

void UStatWidget::UpdateProgressBar_Experience(float _ChangedStat)
{
    if (!IsValid(ProgressBar_Experience) || !HeroStatComponent.IsValid()) return;

    if (HeroStatComponent->GetExpToLevelUp() == 0.0f) return;

    float CurrentExp = HeroStatComponent.Get()->GetCurrentExp();
    float ExpToLevelUp = HeroStatComponent->GetExpToLevelUp();
    UpdateTextBlock_Experience(CurrentExp, ExpToLevelUp);

    float ExpRatio = FMath::Clamp(CurrentExp / ExpToLevelUp, 0.0f, 1.0f);
    ProgressBar_Experience->SetPercent(ExpRatio);
}