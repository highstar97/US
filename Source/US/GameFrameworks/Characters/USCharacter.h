#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "USCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UUSStateComponent;
class UUSCharacterAnimationComponent;

UCLASS(Blueprintable)
class AUSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AUSCharacter();

	virtual void Tick(float DeltaSeconds) override;

	FORCEINLINE UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent.Get(); }

	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom.Get(); }

	FORCEINLINE UUSStateComponent* GetStateComponent() const { return StateComponent.Get(); }

	FORCEINLINE UUSCharacterAnimationComponent* GetCharacterAnimationComponent() const { return CharacterAnimationComponent.Get(); }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UUSCharacterAnimationComponent> CharacterAnimationComponent;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UUSStateComponent> StateComponent;
};