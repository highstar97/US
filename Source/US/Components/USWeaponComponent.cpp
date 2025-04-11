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
	UE_LOG(LogTemp, Warning, TEXT("Weapon Equipped: %s"), *EquippedWeapon->GetActorLabel());

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
	if (!IsValid(EquippedWeapon)) return;

	EquippedWeapon->Uninteract();

	EquippedWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	EquippedWeapon->SetActorRotation(FRotator::ZeroRotator);

	UE_LOG(LogTemp, Warning, TEXT("Weapon Unequipped: %s"), *EquippedWeapon->GetActorLabel());
	EquippedWeapon = nullptr;
}

void UUSWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!IS_VALID_OR_WARN(DefaultWeaponClass, FString::Printf(TEXT("%s의 BP에서 Default Weapon Class가 할당되지 않음."),*GetOwner()->GetActorLabel()))) return;

	// 게임 시작 시, 기본 무기 할당
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = GetOwner()->GetInstigator();
	AUSWeapon* SpawnedWeapon = GetWorld()->SpawnActor<AUSWeapon>(DefaultWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	if (!IsValid(SpawnedWeapon)) return;
		
	SpawnedWeapon->Interact(Cast<AUSCombatCharacter>(GetOwner()));
}