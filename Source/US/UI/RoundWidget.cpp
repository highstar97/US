#include "UI/RoundWidget.h"

#include "DataValidator.h"
#include "GameStates/USGameState.h"
#include "Components/RoundManageComponent.h"

#include "Components/TextBlock.h"
#include "Animation/WidgetAnimation.h"

void URoundWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TextBlock_RoundStart->SetVisibility(ESlateVisibility::Hidden);

	AUSGameState* USGameState = GetWorld() ? GetWorld()->GetGameState<AUSGameState>() : nullptr;
	if (IsValid(USGameState))
	{
		URoundManageComponent* _RoundManageComponent = USGameState->GetRoundManageComponent();
		if (IsValid(_RoundManageComponent))
		{
			BindRoundManageComponent(_RoundManageComponent);
		}
	}
}

void URoundWidget::BindRoundManageComponent(URoundManageComponent* _RoundManageComponent)
{
	if (!IS_VALID_OR_WARN(_RoundManageComponent, TEXT("RoundWidget에 RoundManageComponent가 제대로 할당되지 않음."))) return;

	RoundManageComponent = _RoundManageComponent;

	RoundManageComponent->OnRoundStarted.AddDynamic(this, &URoundWidget::StartRound);
	RoundManageComponent->OnUpdateNumOfEnemy.AddDynamic(this, &URoundWidget::UpdateNumOfEnmey);
}

void URoundWidget::StartRound(int32 _CurrentRound)
{
	if (!IsValid(TextBlock_CurrentRound) || !IsValid(Animation_RoundStart)) return;
	
	TextBlock_CurrentRound->SetText(FText::FromString(FString::Printf(TEXT("Round : %d"), _CurrentRound)));

	PlayAnimation(Animation_RoundStart);
}

void URoundWidget::UpdateNumOfEnmey(int32 _NumOfAliveEnmey, int32 _NumOfSpawnedEnemy)
{
	if (!IsValid(TextBlock_NumOfEnemy) || !RoundManageComponent.IsValid()) return;

	TextBlock_NumOfEnemy->SetText(FText::FromString(FString::Printf(TEXT("Enemy : %d / %d"), _NumOfAliveEnmey, _NumOfSpawnedEnemy)));
}