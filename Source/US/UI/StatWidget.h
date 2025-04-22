#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatWidget.generated.h"

class UUSStatComponent;
class UUSHeroStatComponent;
class UTextBlock;
class UProgressBar;

UCLASS()
class US_API UStatWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindCharacterStat(UUSStatComponent* _StatComponent);

private:
	UFUNCTION()
	void UpdateTextBlock_Name(); // TODO : Make Profile about Character.
	
	UFUNCTION()
	void UpdateTextBlock_Level(int32 _Level);
	
	UFUNCTION()
	void UpdateTextBlock_Attack(float _Attack);
	
	UFUNCTION()
	void UpdateTextBlock_Defense(float _Defense);
	
	UFUNCTION()
	void UpdateTextBlock_AttackSpeed(float _AttackSpeed);
	
	void UpdateTextBlock_Health(const float _CurrentHealth, const float _MaxHealth);

	void UpdateTextBlock_Experience(const float _CurrentExp, const float _ExpToLevelUp);

	UFUNCTION()
	void UpdateProgressBar_Health(float _ChangedStat);
	
	UFUNCTION()
	void UpdateProgressBar_Experience(float _ChangedStat);

private:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "MyVariable | Stat ")
	TObjectPtr<UTextBlock> TextBlock_Name;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "MyVariable | Stat ")
	TObjectPtr<UTextBlock> TextBlock_Level;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "MyVariable | Stat ")
	TObjectPtr<UTextBlock> TextBlock_Attack;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "MyVariable | Stat ")
	TObjectPtr<UTextBlock> TextBlock_Defense;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "MyVariable | Stat ")
	TObjectPtr<UTextBlock> TextBlock_AttackSpeed;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "MyVariable | Stat ")
	TObjectPtr<UTextBlock> TextBlock_Health;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "MyVariable | Stat ")
	TObjectPtr<UTextBlock> TextBlock_Experience;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "MyVariable | Stat ")
	TObjectPtr<UProgressBar> ProgressBar_Health;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "MyVariable | Stat ")
	TObjectPtr<UProgressBar> ProgressBar_Experience;

	TWeakObjectPtr<UUSHeroStatComponent> HeroStatComponent;
};