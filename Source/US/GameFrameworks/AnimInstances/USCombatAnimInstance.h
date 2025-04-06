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

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable | State", meta = (AllowPrivateAccess = "true"), BlueprintGetter = GetIsInCombat)
    bool bIsInCombat;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable | State", meta = (AllowPrivateAccess = "true"), BlueprintGetter = GetIsWeaponEquipped)
    bool bIsWeaponEquipped;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable", meta = (AllowPrivateAccess = "true"))
    TWeakObjectPtr<AUSCombatCharacter> CombatCharacter;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable", meta = (AllowPrivateAccess = "true"))
    TWeakObjectPtr<UUSCombatComponent> CombatComponent;
};