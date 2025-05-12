#include "USGameInstance.h"

#include "USAnimationSharingSystem.h"

UUSGameInstance::UUSGameInstance()
{

}

void UUSGameInstance::UpdateActorAnimationState(AActor* Actor, EState NewState)
{
	if (!IsValid(AnimationSharingSystem))
	{
		AnimationSharingSystem = NewObject<UUSAnimationSharingSystem>(this, AnimationSharingSystemClass);
	}

	AnimationSharingSystem->UpdateActorAnimationState(Actor, NewState);
}