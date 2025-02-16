#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterHealthWidget.generated.h"

class UUSStatComponent;
class UProgressBar;

UCLASS()
class US_API UCharacterHealthWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindCharacterStat(UUSStatComponent* StatComponent);

private:
	// Update ProgressBar_CharacterHealth
	// @param '_ChangedStat' is input from delgate. Not use.
	UFUNCTION()
	void UpdateProgressBar(float _ChangedStat);

	TWeakObjectPtr<UUSStatComponent> StatComponent;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Stat")
	TObjectPtr<UProgressBar> ProgressBar_CharacterHealth;
};