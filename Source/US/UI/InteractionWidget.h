#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"

struct FInteractableData;
class AUSCharacter;
class UTextBlock;
class UProgressBar;

UCLASS()
class US_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateWidget(const FInteractableData* InteractableData) const;

	UFUNCTION(Category = "Interaction | Interactable Data")
	float UpdateInteractionProgress();

	void SetInteractionProgress(float Progress);

protected:
	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Interaction Widget | Interactable Data")
	float CurrentInteractionDuration;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interactable Data")
	TObjectPtr<UTextBlock> TextBlock_Name;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interactable Data")
	TObjectPtr<UTextBlock> TextBlock_Action;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interactable Data")
	TObjectPtr<UTextBlock> TextBlock_Quantity;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interactable Data")
	TObjectPtr<UTextBlock> TextBlock_InteractableType;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interactable Data")
	TObjectPtr<UProgressBar> ProgressBar_Interaction;
};