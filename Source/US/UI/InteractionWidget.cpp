#include "InteractionWidget.h"

#include "Interfaces/InteractionInterface.h"

#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UInteractionWidget::UpdateWidget(const FInteractableData* InteractableData) const
{
	if (!InteractableData) return;

	TextBlock_Name.Get()->SetText(InteractableData->Name);
	TextBlock_Action.Get()->SetText(InteractableData->Action);

	if (InteractableData->Quantity < 2)
	{
		TextBlock_Quantity.Get()->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		TextBlock_Quantity.Get()->SetText(FText::Format(FText::FromString("x{0}"), InteractableData->Quantity));
		TextBlock_Quantity.Get()->SetVisibility(ESlateVisibility::Visible);
	}

	switch (InteractableData->InteractableType)
	{
	case EInteractableType::PRESSSHORT:
	{
		TextBlock_InteractableType.Get()->SetText(FText::FromString("Press Short"));
		ProgressBar_Interaction.Get()->SetVisibility(ESlateVisibility::Collapsed);
		break;
	}
	case EInteractableType::PRESSLONG:
	{
		TextBlock_InteractableType.Get()->SetText(FText::FromString("Press Long"));
		ProgressBar_Interaction.Get()->SetVisibility(ESlateVisibility::Visible);
		break;
	}
	default:
	{
		break;
	}
	}
}

void UInteractionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (IsValid(ProgressBar_Interaction))
	{
		ProgressBar_Interaction.Get()->PercentDelegate.BindUFunction(this, "UpdateInteractionProgress");
	}
}

void UInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CurrentInteractionDuration = 0.0f;
	TextBlock_InteractableType.Get()->SetText(FText::FromString("Press Short"));
}

float UInteractionWidget::UpdateInteractionProgress()
{
	if (IsValid(ProgressBar_Interaction))
	{
		return ProgressBar_Interaction->GetPercent();
	}

	return 0.0f;
}

void UInteractionWidget::SetInteractionProgress(float Progress)
{
	if (IsValid(ProgressBar_Interaction))
	{
		ProgressBar_Interaction->SetPercent(Progress);
	}
}