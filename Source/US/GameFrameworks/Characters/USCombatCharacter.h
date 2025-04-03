#pragma once

#include "CoreMinimal.h"
#include "Characters/USCharacter.h"
#include "USCombatCharacter.generated.h"

class UUSCombatComponent;
class UUSStatComponent;
class UWidgetComponent;
class UCharacterHealthWidget;

UCLASS()
class US_API AUSCombatCharacter : public AUSCharacter
{
	GENERATED_BODY()

public:
	AUSCombatCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	FORCEINLINE UUSCombatComponent* GetCombatComponent() const { return CombatComponent; }

	FORCEINLINE UUSStatComponent* GetStatComponent() const { return StatComponent; }

	void Attack();

private:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void DelayedBeginPlay();

	void InitCapsuleCollision();

	void InitStatComponent();

	void InitCharacterHealthWidgetComponent();

	UFUNCTION()
	void HandleDeath();

	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UUSCombatComponent> CombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UUSStatComponent> StatComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetComponent> CharacterHealthWidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCharacterHealthWidget> CharacterHealthWidgetClass;
};