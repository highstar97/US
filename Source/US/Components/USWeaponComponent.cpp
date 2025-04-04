#include "USWeaponComponent.h"

#include "DataValidator.h"
#include "Characters/USCombatCharacter.h"
#include "Weapons/USWeapon.h"

UUSWeaponComponent::UUSWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UUSWeaponComponent::EquipWeapon(AUSWeapon* NewWeapon)
{
	if (NewWeapon == nullptr) return;

	if (EquippedWeapon != nullptr)
	{
		UnequipWeapon();
	}

	EquippedWeapon = NewWeapon;
	UE_LOG(LogTemp, Warning, TEXT("Weapon Equipped: %s"), *NewWeapon->GetActorLabel());

	if (AUSCombatCharacter* CombatCharacter = Cast<AUSCombatCharacter>(GetOwner()))
	{
		if (USkeletalMeshComponent* Mesh = CombatCharacter->GetMesh())
		{
			FName WeaponSocketR(TEXT("weapon_socket_r"));
			if (Mesh->DoesSocketExist(WeaponSocketR))
			{
				EquippedWeapon->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocketR);
			}
		}
	}
}

void UUSWeaponComponent::UnequipWeapon()
{
	if (EquippedWeapon == nullptr) return;

	EquippedWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	EquippedWeapon->SetActorRotation(FRotator::ZeroRotator);

	UE_LOG(LogTemp, Warning, TEXT("Weapon Unequipped: %s"), *EquippedWeapon->GetActorLabel());
	EquippedWeapon = nullptr;
}

void UUSWeaponComponent::UseWeapon()
{
    EquippedWeapon->Attack();	// CombatComponet에서 Weapon 착용 여부 이미 확인.
}

void UUSWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!IS_VALID_OR_EXIT(DefaultWeaponClass, TEXT("Default Weapon Class가 유효하지 않습니다."))) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = GetOwner()->GetInstigator();
	AUSWeapon* SpawnedWeapon = GetWorld()->SpawnActor<AUSWeapon>(DefaultWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	if (!SpawnedWeapon) return;
		
	SpawnedWeapon->Interact(Cast<AUSCombatCharacter>(GetOwner()));
}