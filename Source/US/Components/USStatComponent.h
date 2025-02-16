#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "USStatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChanged, float, MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurrentHealthChanged, float, CurrentHealth);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class US_API UUSStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UUSStatComponent();

	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }

	void SetMaxHealth(const float _MaxHealth);

	void SetCurrentHealth(const float _CurrentHealth);

	void TakeDamage(float DamageAmount);

	FOnMaxHealthChanged OnMaxHealthChanged;

	FOnCurrentHealthChanged OnCurrentHealthChanged;

	FOnCharacterDeath OnCharacterDeath;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = Stat, meta = (AllowPrivateAccess = "true"))
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, Category = Stat, meta = (AllowPrivateAccess = "true"))
	float CurrentHealth;
};