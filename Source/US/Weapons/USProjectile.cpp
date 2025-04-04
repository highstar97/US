#include "Weapons/USProjectile.h"

#include "Weapons/Datas/ProjectileDataAsset.h"

AUSProjectile::AUSProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
    RootComponent = MeshComponent;
    SetActorTickEnabled(false);
}

void AUSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (!bIsActive || !ProjectileDataAsset) return;

    SetActorLocation(GetActorLocation() + Velocity * DeltaTime);
    ElapsedTime += DeltaTime;
    if (ElapsedTime >= ProjectileDataAsset->LifeTime)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s Deactive"), *GetActorLabel());
        DeactivateProjectile();
    }
}

void AUSProjectile::InitProjectile(const UProjectileDataAsset* _ProjectileDataAsset)
{
    ProjectileDataAsset = _ProjectileDataAsset;

    MeshComponent->SetStaticMesh(ProjectileDataAsset->Mesh);
    SetActorScale3D(_ProjectileDataAsset->Scale);
    bIsActive = false;
}

void AUSProjectile::ActivateProjectile(FVector Location, FVector Direction)
{
    if (!IsValid(ProjectileDataAsset)) return;

    SetActorLocation(Location);
    SetActorRotation(Direction.Rotation());

    Velocity = Direction * ProjectileDataAsset->Speed;
    ElapsedTime = 0.0f;
    
    bIsActive = true;
    SetActorHiddenInGame(false);
    SetActorEnableCollision(true);
    SetActorTickEnabled(true);

    UE_LOG(LogTemp, Warning, TEXT("%s Active"), *GetActorLabel());
}

void AUSProjectile::DeactivateProjectile()
{
    SetActorLocation(FVector::ZeroVector);
    SetActorRotation(FRotator::ZeroRotator);

    bIsActive = false;
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
    SetActorTickEnabled(false);
}

void AUSProjectile::BeginPlay()
{
	Super::BeginPlay();
}