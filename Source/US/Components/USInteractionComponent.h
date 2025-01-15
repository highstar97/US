#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/InteractionInterface.h"
#include "USInteractionComponent.generated.h"

class AUSPlayerController;
class AUSCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class US_API UUSInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UUSInteractionComponent();

	TOptional<bool> IsInteractShort() const;

	void InteractShort();
	
	void InteractLong();

	void CancelInteraction();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void ShowInteractionUI();

	void HideInteractionUI();

	void UpdateInteractionWidget();

	void CompleteInteraction();

private:
	FTimerHandle InteractionProgressHandle;
	FTimerHandle InteractionTimerHandle;

	TObjectPtr<AUSPlayerController> PlayerController;
	TWeakObjectPtr<AUSCharacter> PlayerCharacter;

	TScriptInterface<IInteractionInterface> CurrentInteractable;
};