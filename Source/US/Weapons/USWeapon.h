#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapons/Datas/WeaponData.h"
#include "Interfaces/InteractionInterface.h"
#include "USWeapon.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;
class UPostProcessComponent;
class UWeaponDataAsset;

UCLASS()
class US_API AUSWeapon : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	AUSWeapon();

	virtual void Attack();

	virtual void Interact(ACharacter* Interactor) override;

	void Uninteract();

	float GetRange() const;

	FVector GetMuzzleLocation() const;

protected:
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable | Component ", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> InteractionCapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable | Component ", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable | Component ", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPostProcessComponent> PostProcessComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyVariable | Data Asset | Need To Edit", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWeaponDataAsset> WeaponDataAsset;

	TWeakObjectPtr<ACharacter> OwnerCharacter;

private:
	void Initialize();

	void SetWeaponOutlineColor();
};