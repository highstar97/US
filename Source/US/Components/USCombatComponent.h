#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "USCombatComponent.generated.h"

class UUSWeaponComponent;
class AUSWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class US_API UUSCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UUSCombatComponent();

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool GetIsInCombat() const { return bIsInCombat; }

	AUSWeapon* GetEquippedWeapon() const;

	FORCEINLINE UUSWeaponComponent* GetWeaponComponent() const { return WeaponComponent; }

	bool Attack();

private:
	void EnterCombat();

	void ExitCombat();

	void ResetCombatTimer();

private:
	UPROPERTY(VisibleAnywhere, Category = "MyVariable | State ", meta = (AllowPrivateAccess = "true"), BlueprintGetter = GetIsInCombat)
	bool bIsInCombat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable | Weapon ", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UUSWeaponComponent> WeaponComponent;

	const float CombatTimeoutThreshold = 3.0f;

	FTimerHandle CombatTimerHandle;
};