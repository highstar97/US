#include "Weapons/USProjectile.h"

#include "Characters/USCombatCharacter.h"
#include "Weapons/Datas/ProjectileDataAsset.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

AUSProjectile::AUSProjectile()
{
    PrimaryActorTick.bCanEverTick = true;

    CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
    CollisionComponent->SetCollisionProfileName("Projectile");
    CollisionComponent->SetGenerateOverlapEvents(true);         // 변경됨: Overlap 감지
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);   // 변경됨: Query만 사용
    RootComponent = CollisionComponent;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
    MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    MeshComponent->SetupAttachment(RootComponent);

    bIsActive = false;
    ElapsedTime = 0.0f;

    SetActorTickEnabled(false);
}

void AUSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (!bIsActive || !ProjectileDataAsset || !OwnerCharacter.IsValid())
    {
        DeactivateProjectile();
        return;
    }

    SetActorLocation(GetActorLocation() + Velocity * DeltaTime);
    ElapsedTime += DeltaTime;
    if (ElapsedTime >= ProjectileDataAsset->LifeTime)
    {
        DeactivateProjectile();
    }
}

void AUSProjectile::Init(const UProjectileDataAsset* _ProjectileDataAsset)
{
    ProjectileDataAsset = _ProjectileDataAsset;

    MeshComponent->SetStaticMesh(ProjectileDataAsset->Mesh);
    SetActorScale3D(_ProjectileDataAsset->Scale);

    // Mesh의 Bounds를 기준으로 자동 추정
    FVector Extent = ProjectileDataAsset->Mesh->GetBounds().BoxExtent * _ProjectileDataAsset->Scale;

    float EstimatedRadius = FMath::Max(Extent.X, Extent.Y);
    float EstimatedHalfHeight = Extent.Z;

    CollisionComponent->SetCapsuleRadius(EstimatedRadius + 50);
    CollisionComponent->SetCapsuleHalfHeight(EstimatedHalfHeight + 50);

    bIsActive = false;
}

void AUSProjectile::ActivateProjectile(FVector Location, FVector Direction, AUSCombatCharacter* _OwnerCharacter)
{
    if (!IsValid(ProjectileDataAsset)) return;

    SetActorLocation(Location);
    SetActorRotation(Direction.Rotation());

    Velocity = Direction * ProjectileDataAsset->Speed;
    ElapsedTime = 0.0f;
    OwnerCharacter = _OwnerCharacter;
    
    bIsActive = true;
    SetActorHiddenInGame(false);
    SetActorEnableCollision(true);
    SetActorTickEnabled(true);

    // UE_LOG(LogTemp, Warning, TEXT("%s Active"), *GetActorLabel());
}

void AUSProjectile::DeactivateProjectile()
{
    SetActorLocation(FVector::ZeroVector);
    SetActorRotation(FRotator::ZeroRotator);
    OwnerCharacter = nullptr;

    bIsActive = false;
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
    SetActorTickEnabled(false);

    // UE_LOG(LogTemp, Warning, TEXT("%s Deactive"), *GetActorLabel());
}

void AUSProjectile::BeginPlay()
{
    Super::BeginPlay();
    
    if (CollisionComponent)
    {
            CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AUSProjectile::OnProjectileOverlap);
    }
}

void AUSProjectile::OnProjectileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!OwnerCharacter.IsValid()) return;

    if (OtherActor == nullptr || OtherActor == OwnerCharacter.Get() || OtherActor == this) return;

    DrawDebugSphere(GetWorld(), SweepResult.ImpactPoint, 10.f, 12, FColor::Green, false, 1.0f);
    
    // 캐릭터 충돌 시 데미지 처리
    AUSCombatCharacter* CombatCharacter = Cast<AUSCombatCharacter>(OtherActor);
    if(!IsValid(CombatCharacter)) return;

    bool bIsTeam = OwnerCharacter.Get()->IsPlayerControlled() == CombatCharacter->IsPlayerControlled();
    if (bIsTeam)
    {
        return;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("%s Hit by %s"), *OtherActor->GetActorLabel(), *OwnerCharacter.Get()->GetActorLabel());
        UGameplayStatics::ApplyDamage(CombatCharacter, 100.0f, GetInstigatorController(), this, nullptr);
    }

    // 투사체 제거
    DeactivateProjectile();
}