#include "Weapons/USGun.h"

#include "Characters/USCombatCharacter.h"
#include "Components/USCombatComponent.h"
#include "Components/USWeaponComponent.h"
#include "Weapons/WeaponDataAsset.h"

#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"

AUSGun::AUSGun()
{
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(RootComponent);
	ArrowComponent->SetRelativeLocation(FVector(0.0f, 50.0f, 0.0f));
	ArrowComponent->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	ArrowComponent->SetHiddenInGame(false);
}

void AUSGun::Attack()
{
	Super::Attack();

	if (!ensure(WeaponDataAsset != nullptr)) return;

	float InitDamage = WeaponDataAsset->NumericData.Damage;

	UE_LOG(LogTemp, Warning, TEXT("%s Attack!"), *this->GetActorLabel());

	FVector StartLocation = ArrowComponent->GetComponentLocation() + FVector(0.0f, 42.0f, 0.0f);
	FVector ForwardVector = ArrowComponent->GetForwardVector();
	const float Distance = 10000.0f;
	FVector EndLocation = StartLocation + (ForwardVector * Distance);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	TArray<TWeakObjectPtr<const AActor>> IgnoredActors;
	IgnoredActors.Add(this);
	if (OwnerCharacter.IsValid())
	{
		IgnoredActors.Add(OwnerCharacter.Get());
	}
	QueryParams.AddIgnoredActors(IgnoredActors);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_GameTraceChannel3, QueryParams);
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 1.0f, 0, 2.0f);
	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		
		if (HitActor)
		{
			if (AUSCombatCharacter* HitCharacter = Cast<AUSCombatCharacter>(HitActor))
			{
				UE_LOG(LogTemp, Warning, TEXT("Hit Character: %s"), *HitCharacter->GetName());
				DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 12, FColor::Green, false, 1.0f);
				UGameplayStatics::ApplyDamage(HitCharacter, InitDamage, GetInstigatorController(), this, UDamageType::StaticClass());
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No target hit."));
	}
}

void AUSGun::Interact(ACharacter* Interactor)
{
	Super::Interact(Interactor);

	if (AUSCombatCharacter* Character = Cast<AUSCombatCharacter>(Interactor))
	{
		if (UUSWeaponComponent* WeaponComponent = Character->GetCombatComponent()->GetWeaponComponent())
		{
			UE_LOG(LogTemp, Warning, TEXT("%s interact with %s!"), *Character->GetActorLabel(), *GetActorLabel());
			WeaponComponent->EquipWeapon(this);
		}
	}
}