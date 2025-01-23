#pragma once

#include "CoreMinimal.h"
#include "Characters/USCharacter.h"
#include "USCombatCharacter.generated.h"

class UUSCombatComponent;

UCLASS()
class US_API AUSCombatCharacter : public AUSCharacter
{
	GENERATED_BODY()

public:
	AUSCombatCharacter();

	virtual void BeginPlay() override;

	FORCEINLINE UUSCombatComponent* GetCombatComponent() const { return CombatComponent; }

private:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Attack();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UUSCombatComponent> CombatComponent;
};