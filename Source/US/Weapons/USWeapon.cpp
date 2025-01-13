#include "USWeapon.h"

#include "Characters/USCombatCharacter.h"
#include "Components/USWeaponComponent.h"
#include "Weapons/WeaponDataAsset.h"

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
	UE_LOG(LogTemp, Warning, TEXT("Weapon Attack!"));
}

void AUSWeapon::Interact(ACharacter* Interactor)
{
	AUSCombatCharacter* Character = Cast<AUSCombatCharacter>(Interactor);
	if (Character && Character->GetWeaponComponent())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s interact with %s!"), *Character->GetName(), *GetName());
	}
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
	if (DataAsset)
	{
		WeaponMesh->SetStaticMesh(DataAsset->AssetData.Mesh);

		InteractableData.Name = DataAsset->TextData.Name;
		InteractableData.Action = DataAsset->TextData.Purpose;
		InteractableData.Quantity = DataAsset->NumericData.Quantity;
		InteractableData.InteractionDuration = DataAsset->NumericData.InteractionDuration;
		InteractableData.InteractableType = DataAsset->NumericData.InteractionDuration > 0.0f ? EInteractableType::PRESSLONG : EInteractableType::PRESSSHORT;

		SetWeaponOutlineColor();
	}
}

void AUSWeapon::SetWeaponOutlineColor()
{
	if (WeaponMesh && DataAsset)
	{
		WeaponMesh->CustomDepthStencilValue = static_cast<uint8>(DataAsset->Rarity);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Weapon Rarity not found in map!"));
	}
}