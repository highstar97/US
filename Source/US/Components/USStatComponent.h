#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "USStatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChanged, float, MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurrentHealthChanged, float, CurrentHealth);

class UDataTable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class US_API UUSStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UUSStatComponent();

	// Getter
	FORCEINLINE int32 GetLevel() const { return Level; }

	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }

	FORCEINLINE float GetAttack() const { return Attack; }

	FORCEINLINE float GetDefense() const { return Defense; }

	FORCEINLINE float GetAttackSpeed() const { return AttackSpeed; }

	// Setter
	void SetLevel(const int32 _Level);

	void SetMaxHealth(const float _MaxHealth);

	void SetCurrentHealth(const float _CurrentHealth);

	void SetAttack(const float _Attack);

	void SetDefense(const float _Defense);

	void SetAttackSpeed(const float _AttackSpeed);

	// Function
	void LoadStatsAccordingToLevel();

	void TakeDamage(float DamageAmount);
	
	// Delegate
	FOnMaxHealthChanged OnMaxHealthChanged;

	FOnCurrentHealthChanged OnCurrentHealthChanged;

	FOnCharacterDeath OnCharacterDeath;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "MyVariable | Data Config | Need To Edit", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDataTable> DataTable_StatByLevel;

	UPROPERTY(VisibleAnywhere, Category = "MyVariable | Stat ", meta = (AllowPrivateAccess = "true"))
	int32 Level; 
	
	UPROPERTY(VisibleAnywhere, Category = "MyVariable | Stat ", meta = (AllowPrivateAccess = "true"))
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, Category = "MyVariable | Stat ", meta = (AllowPrivateAccess = "true"))
	float CurrentHealth;

	UPROPERTY(VisibleAnywhere, Category = "MyVariable | Stat ", meta = (AllowPrivateAccess = "true"))
	float Attack;

	UPROPERTY(VisibleAnywhere, Category = "MyVariable | Stat ", meta = (AllowPrivateAccess = "true"))
	float Defense;

	UPROPERTY(VisibleAnywhere, Category = "MyVariable | Stat ", meta = (AllowPrivateAccess = "true"))
	float AttackSpeed;
};