#pragma once

#include "CoreMinimal.h"
#include "Characters/USCharacter.h"
#include "USCombatCharacter.generated.h"

class UUSCombatComponent;
class UUSStatComponent;
class AUSWeapon;
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

	AUSWeapon* GetEquippedWeapon() const;

	void EquipWeapon(AUSWeapon* NewWeapon);

	void Attack();

	virtual void AddExp(const float _Exp);

protected:
	UFUNCTION()
	virtual void HandleDeath();

	UFUNCTION()
	virtual void HandleLevel(const int32 _Level);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable | Component ", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UUSStatComponent> StatComponent;

private:
	void DelayedBeginPlay();

	void InitCapsuleCollision();

	void InitStatComponent();

	void InitCharacterHealthWidgetComponent();

	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable | Component ", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UUSCombatComponent> CombatComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable | UI ", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetComponent> CharacterHealthWidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MyVariable | UI | Need To Edit", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCharacterHealthWidget> CharacterHealthWidgetClass;
};