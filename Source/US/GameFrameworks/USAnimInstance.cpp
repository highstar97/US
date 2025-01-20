#include "USAnimInstance.h"

#include "Characters/USCharacter.h"
#include "Components/USStateComponent.h"

UUSAnimInstance::UUSAnimInstance()
{

}

void UUSAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    AUSCharacter* OwnerCharacter = Cast<AUSCharacter>(TryGetPawnOwner());
    if (IsValid(OwnerCharacter))
    {
        StateComponent = OwnerCharacter->GetStateComponent();
    }
}

void UUSAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);
}