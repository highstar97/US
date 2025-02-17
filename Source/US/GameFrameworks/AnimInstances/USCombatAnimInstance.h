#pragma once

#include "CoreMinimal.h"
#include "USAnimInstance.h"
#include "USCombatAnimInstance.generated.h"

class AUSCombatCharacter;
class UUSCombatComponent;

UCLASS()
class US_API UUSCombatAnimInstance : public UUSAnimInstance
{
	GENERATED_BODY()
	
public:
    UUSCombatAnimInstance();

    virtual void NativeInitializeAnimation() override;

    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

    UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
    bool GetIsInCombat() const { return bIsInCombat; }

    UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
    bool GetIsWeaponEquipped() const { return bIsWeaponEquipped; }

private:
    UFUNCTION()
    void AnimNotify_DisableInput();

    UFUNCTION()
    void AnimNotify_EnableInput();

    UFUNCTION()
    void AnimNotify_CallAttackLogic();

private:
    UPROPERTY(EditDefaultsOnly, Category = State, meta = (AllowPrivateAccess = "true"), BlueprintGetter = GetIsInCombat)
    bool bIsInCombat;

    UPROPERTY(EditDefaultsOnly, Category = State, meta = (AllowPrivateAccess = "true"), BlueprintGetter = GetIsWeaponEquipped)
    bool bIsWeaponEquipped;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TWeakObjectPtr<AUSCombatCharacter> CombatCharacter;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TWeakObjectPtr<UUSCombatComponent> CombatComponent;
};