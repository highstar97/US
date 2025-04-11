#include "USWeapon.h"

#include "Weapons/Datas/WeaponDataAsset.h"

#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PostProcessComponent.h"

AUSWeapon::AUSWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	InteractionCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("InteractionCapsuleComponent"));
	InteractionCapsuleComponent->InitCapsuleSize(50.0f, 50.0f);
	InteractionCapsuleComponent->SetCollisionProfileName(TEXT("Weapon"));
	RootComponent = InteractionCapsuleComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetRenderCustomDepth(true);

	PostProcessComponent = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcessComponent"));
	PostProcessComponent->SetupAttachment(MeshComponent);
	PostProcessComponent->bUnbound = false;
	// TODO : M_PostProcessAboutRarity C++에서 추가할 수 있으면 추가하기.
}

void AUSWeapon::Attack()
{

}

void AUSWeapon::Interact(ACharacter* Interactor)
{
	if (!IsValid(Interactor)) return;

	if (InteractableData.OwningActor) return;	// 상호작용중인 액터가 있으면 종료

	OwnerCharacter = Interactor;
	InteractableData.OwningActor = Interactor;
}

void AUSWeapon::Uninteract()
{
	if (!InteractableData.OwningActor) return;

	InteractableData.OwningActor = nullptr;
}

float AUSWeapon::GetRange() const
{
	return IsValid(WeaponDataAsset) ? WeaponDataAsset->NumericData.Range : 0.0f;
}

FVector AUSWeapon::GetMuzzleLocation() const
{
	if (MeshComponent->DoesSocketExist(TEXT("MuzzleSocket")))
	{
		return MeshComponent->GetSocketLocation(TEXT("MuzzleSocket"));
	}
	return FVector::ZeroVector;
}

void AUSWeapon::BeginPlay()
{
	Super::BeginPlay();

	Initialize();
}

void AUSWeapon::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SetWeaponOutlineColor();
}

void AUSWeapon::Initialize()
{
	if (IsValid(WeaponDataAsset))
	{
		MeshComponent->SetStaticMesh(WeaponDataAsset->AssetData.Mesh);
		
		SetActorLabel(FText(WeaponDataAsset->TextData.Name).ToString());
		InteractableData.Name = WeaponDataAsset->TextData.Name;
		InteractableData.Action = WeaponDataAsset->TextData.Purpose;
		InteractableData.Quantity = WeaponDataAsset->NumericData.Quantity;
		InteractableData.InteractionDuration = WeaponDataAsset->NumericData.InteractionDuration;
		InteractableData.InteractableType = WeaponDataAsset->NumericData.InteractionDuration > 0.0f ? EInteractableType::PRESSLONG : EInteractableType::PRESSSHORT;
		InteractableData.OwningActor = nullptr;

		SetWeaponOutlineColor();
	}
}

void AUSWeapon::SetWeaponOutlineColor()
{
	if (IsValid(MeshComponent) && IsValid(WeaponDataAsset))
	{
		MeshComponent->CustomDepthStencilValue = static_cast<uint8>(WeaponDataAsset->Rarity);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Weapon Rarity not found in map!"));
	}
}