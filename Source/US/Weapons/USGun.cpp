#include "Weapons/USGun.h"

#include "DataValidator.h"
#include "ProjectileSubsystem.h"
#include "Characters/USCombatCharacter.h"
#include "Controllers/USPlayerController.h"
#include "Controllers/USAIController.h"
#include "Components/USCombatComponent.h"
#include "Components/USWeaponComponent.h"
#include "Weapons/USProjectile.h"
#include "Weapons/Datas/ProjectileDataAsset.h"
#include "Weapons/Datas/WeaponDataAsset.h"

#include "BehaviorTree/BlackboardComponent.h"

AUSGun::AUSGun()
{

}

void AUSGun::Attack()
{
	Super::Attack();

	if (!OwnerCharacter.IsValid() || !MeshComponent) return;

	UProjectileSubsystem* Subsystem = GetWorld()->GetSubsystem<UProjectileSubsystem>();
	if (!IsValid(Subsystem)) return;

	AUSProjectile* Projectile = Subsystem->GetAvailableProjectile(ProjectileDataAsset);
	if (!IsValid(Projectile)) return; 
	
	AController* Controller = OwnerCharacter->GetController();
	if (!Controller) return;

	FVector TargetLocation;
	if (Controller->IsPlayerController())
	{
		AUSPlayerController* PlayerController = Cast<AUSPlayerController>(Controller);
		if (!PlayerController) return;
		
		TargetLocation = PlayerController->GetCrosshairLocation();
	}
	else
	{
		AUSAIController* AIController = Cast<AUSAIController>(Controller);
		if (!AIController) return;

		UBlackboardComponent* Blackboard = AIController->GetBlackboardComponent();
		if (!Blackboard) return;

		AUSCombatCharacter* Target = Cast<AUSCombatCharacter>(Blackboard->GetValueAsObject("TargetActor"));
		if (!Target) return;

		TargetLocation = Target->GetActorLocation();
	}

	FVector MuzzleLocation = GetMuzzleLocation();
	FVector FireDirection = (TargetLocation - MuzzleLocation).GetSafeNormal2D();

	Projectile->ActivateProjectile(MuzzleLocation, FireDirection);

	// 디버깅
	// DrawDebugSphere(GetWorld(), TargetLocation, 10.f, 12, FColor::Red, false, 1.0f);
	// DrawDebugLine(GetWorld(), MuzzleLocation, MuzzleLocation + FireDirection * 500.f, FColor::Green, false, 1.0f, 0, 2.0f);
	// UE_LOG(LogTemp, Warning, TEXT("Shoot %s towards %s"), *Projectile->GetActorLabel(), *TargetLocation.ToString());
}

void AUSGun::Interact(ACharacter* Interactor)
{
	Super::Interact(Interactor);

	if (AUSCombatCharacter* CombatCharacter = Cast<AUSCombatCharacter>(Interactor))
	{
		CombatCharacter->EquipWeapon(this);
		UE_LOG(LogTemp, Warning, TEXT("%s interact with %s!"), *CombatCharacter->GetActorLabel(), *GetActorLabel());
	}
}

void AUSGun::BeginPlay()
{
	Super::BeginPlay();

	if(!IS_VALID_OR_EXIT(ProjectileDataAsset, TEXT("ProjectileDataAsset이 유효하지 않습니다."))) return;

	if (UProjectileSubsystem* Subsystem = GetWorld()->GetSubsystem<UProjectileSubsystem>())
	{
		Subsystem->TryRegisterProjectileInPool(ProjectileDataAsset);
	}
}