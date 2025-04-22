#pragma once

#include "CoreMinimal.h"
#include "Characters/USCombatCharacter.h"
#include "USHeroCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class US_API AUSHeroCharacter : public AUSCombatCharacter
{
	GENERATED_BODY()
	
public:
	AUSHeroCharacter(const FObjectInitializer& ObjectInitializer);

	FORCEINLINE UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent.Get(); }

	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom.Get(); }

	virtual void Tick(float DeltaSeconds) override;

private:
	virtual void AddExp(const float _Exp) override;

	void AttackRepeatedly(float DeltaSeconds);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	float AttackElapsed;
};