#include "USWeapon.h"

#include "Weapons/WeaponDataAsset.h"

#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PostProcessComponent.h"

AUSWeapon::AUSWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	InteractionCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("InteractionCapsuleComponent"));
	InteractionCapsuleComponent->InitCapsuleSize(50.0f, 50.0f);
	InteractionCapsuleComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	RootComponent = InteractionCapsuleComponent;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);
	WeaponMesh->SetRenderCustomDepth(true);

	PostProcessComponent = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcessComponent"));
	PostProcessComponent->SetupAttachment(WeaponMesh);
	PostProcessComponent->bUnbound = false;
	// TODO : M_PostProcessAboutRarity C++에서 추가할 수 있으면 추가하기.
}

void AUSWeapon::Attack()
{

}

void AUSWeapon::Interact(ACharacter* Interactor)
{
	if (!IsValid(Interactor)) return;

	OwnerCharacter = Interactor;
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
		WeaponMesh->SetStaticMesh(WeaponDataAsset->AssetData.Mesh);
		
		SetActorLabel(FText(WeaponDataAsset->TextData.Name).ToString());
		InteractableData.Name = WeaponDataAsset->TextData.Name;
		InteractableData.Action = WeaponDataAsset->TextData.Purpose;
		InteractableData.Quantity = WeaponDataAsset->NumericData.Quantity;
		InteractableData.InteractionDuration = WeaponDataAsset->NumericData.InteractionDuration;
		InteractableData.InteractableType = WeaponDataAsset->NumericData.InteractionDuration > 0.0f ? EInteractableType::PRESSLONG : EInteractableType::PRESSSHORT;

		SetWeaponOutlineColor();
	}
}

void AUSWeapon::SetWeaponOutlineColor()
{
	if (IsValid(WeaponMesh) && IsValid(WeaponDataAsset))
	{
		WeaponMesh->CustomDepthStencilValue = static_cast<uint8>(WeaponDataAsset->Rarity);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Weapon Rarity not found in map!"));
	}
}