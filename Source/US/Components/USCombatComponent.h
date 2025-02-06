#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "USCombatComponent.generated.h"

class UUSWeaponComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class US_API UUSCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UUSCombatComponent();

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool GetIsInCombat() const { return bIsInCombat; }

	TOptional<bool> GetIsWeaponEquipped() const;

	FORCEINLINE UUSWeaponComponent* GetWeaponComponent() const { return WeaponComponent; }

	void Attack();

protected:
	virtual void BeginPlay() override;

private:
	void EnterCombat();

	void ExitCombat();

	void ResetCombatTimer();

private:
	const float CombatTimeoutDuration = 3.0f;

	FTimerHandle CombatTimerHandle;

	UPROPERTY(EditDefaultsOnly, Category = State, meta = (AllowPrivateAccess = "true"), BlueprintGetter = GetIsInCombat)
	bool bIsInCombat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UUSWeaponComponent> WeaponComponent;
};