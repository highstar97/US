#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapons/WeaponData.h"
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

protected:
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> InteractionCapsuleComponent;

	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPostProcessComponent> PostProcessComponent;

	UPROPERTY(Category = Weapon, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWeaponDataAsset> WeaponDataAsset;

	TWeakObjectPtr<ACharacter> OwnerCharacter;

private:
	void Initialize();

	void SetWeaponOutlineColor();
};