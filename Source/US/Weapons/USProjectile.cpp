#include "Weapons/USProjectile.h"

#include "Characters/USCombatCharacter.h"
#include "Weapons/Datas/ProjectileDataAsset.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

AUSProjectile::AUSProjectile()
{
    PrimaryActorTick.bCanEverTick = true;

    CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
    CollisionComponent->SetCollisionObjectType(ECC_GameTraceChannel3);              // ECC_GameTraceChannel1 is 'Attack'
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

    UE_LOG(LogTemp, Warning, TEXT("%s Active"), *GetActorLabel());
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

    UE_LOG(LogTemp, Warning, TEXT("%s Deactive"), *GetActorLabel());
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
    UE_LOG(LogTemp, Warning, TEXT("%s Hit by %s"), *OtherActor->GetActorLabel(), *OwnerCharacter.Get()->GetActorLabel());

    // 캐릭터 충돌 시 데미지 처리
    AUSCombatCharacter* HitCharacter = Cast<AUSCombatCharacter>(OtherActor);
    if (HitCharacter)
    {
        // 데미지 처리 (원하면 DamageType 전달도 가능
        UGameplayStatics::ApplyDamage(HitCharacter, 100.0f, GetInstigatorController(), this, nullptr);
        // 히트 이펙트 등 추가 가능
    }
    else
    {
        // 환경 오브젝트 등에 부딪힘 (예: 벽, 상자, 지형 등)
        // 원하면 파티클, 사운드 재생 가능
    }

    // 투사체 제거
    DeactivateProjectile();
}