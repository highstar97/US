#include "UI/CharacterHealthWidget.h"

#include "Components/USStatComponent.h"

#include "Components/ProgressBar.h"

void UCharacterHealthWidget::BindCharacterStat(UUSStatComponent* _StatComponent)
{
	if (!IsValid(_StatComponent)) return;

    StatComponent = _StatComponent;
    _StatComponent->OnMaxHealthChanged.AddDynamic(this, &UCharacterHealthWidget::UpdateProgressBar);
    _StatComponent->OnCurrentHealthChanged.AddDynamic(this, &UCharacterHealthWidget::UpdateProgressBar);

    UpdateProgressBar(0.0f);
}

void UCharacterHealthWidget::UpdateProgressBar(float _ChangedStat)
{
    if (!IsValid(ProgressBar_CharacterHealth) || !StatComponent.IsValid()) return;

    if (StatComponent->GetMaxHealth() == 0.0f) return;

    float HealthRatio = FMath::Clamp(StatComponent.Get()->GetCurrentHealth() / StatComponent->GetMaxHealth(), 0.0f, 1.0f);
    ProgressBar_CharacterHealth->SetPercent(HealthRatio);
}