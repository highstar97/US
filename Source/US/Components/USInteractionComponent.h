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

	void HandleInteract();

	void InteractShort();
	
	void InteractLong();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void ShowInteractionUI();

	void HideInteractionUI();

	bool IsReadyToInteract();

	void UpdateInteractLong();

	void UpdateInteractionProgress();

	void CompleteInteraction();

	void FailedtoInteract();

private:
	FTimerHandle InteractionProgressHandle;
	FTimerHandle InteractionTimerHandle;

	TObjectPtr<AUSPlayerController> OwnerController;
	TWeakObjectPtr<AUSCharacter> OwnerCharacter;

	TScriptInterface<IInteractionInterface> CurrentInteractable;
};