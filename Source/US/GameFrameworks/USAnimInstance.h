#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "USAnimInstance.generated.h"

class AUSCharacter;
class UCharacterMovementComponent;
class UUSStateComponent;

UCLASS()
class US_API UUSAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UUSAnimInstance();

    virtual void NativeInitializeAnimation() override;

    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintPure)
	UUSStateComponent* GetStateComponent() const { return StateComponent.Get(); }

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TWeakObjectPtr<UUSStateComponent> StateComponent;
};