#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "USCharacter.generated.h"

class UUSCharacterAnimationComponent;
class UUSStateComponent;

UCLASS(Blueprintable)
class AUSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AUSCharacter(const FObjectInitializer& ObjectInitializer);

	FORCEINLINE UUSStateComponent* GetStateComponent() const { return StateComponent.Get(); }

	FORCEINLINE UUSCharacterAnimationComponent* GetCharacterAnimationComponent() const { return CharacterAnimationComponent.Get(); }
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable | Component ", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UUSCharacterAnimationComponent> CharacterAnimationComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable | Component ", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UUSStateComponent> StateComponent;
};