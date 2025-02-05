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

	if (!OwnerCharacter.IsValid()) return;
	if (!IsValid(WeaponDataAsset)) return;

	float InitDamage = WeaponDataAsset->NumericData.Damage;
	UE_LOG(LogTemp, Warning, TEXT("%s Attack!"), *this->GetActorLabel());

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!IsValid(PlayerController)) return;

	FHitResult HitResult;
	if (!PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, HitResult)) return;

	DrawDebugSphere(GetWorld(), HitResult.Location, 1.f, 12, FColor::Green, false, 1.0f);

	FVector CharacterToHit = HitResult.Location - OwnerCharacter->GetActorLocation();
	CharacterToHit.Z = 0.f;
	CharacterToHit.Normalize();

	FVector CharacterForward = OwnerCharacter->GetActorForwardVector();
	CharacterForward.Z = 0.f;
	CharacterForward.Normalize();

	float DotProduct = FVector::DotProduct(CharacterToHit, CharacterForward);
	DotProduct = FMath::Clamp(DotProduct, -1.0f, 1.0f);
	float AngleRadians = FMath::Acos(DotProduct);
	float AngleDegrees = FMath::RadiansToDegrees(AngleRadians);

	FVector OuterProduct = FVector::CrossProduct(CharacterForward, CharacterToHit);
	if (OuterProduct.Z < 0.f)
	{
		AngleDegrees = -AngleDegrees;
	}

	FRotator NewRotation = OwnerCharacter->GetActorRotation();
	NewRotation.Yaw += AngleDegrees;
	OwnerCharacter->SetActorRotation(NewRotation);

	// Ray Trace
	FVector TraceStart = ArrowComponent->GetComponentLocation();
	const float TraceDistance = 10000.0f;
	FVector TraceEnd = TraceStart + (OwnerCharacter->GetActorForwardVector() * TraceDistance);

	HitResult.Reset();
	FCollisionQueryParams QueryParams;
	TArray<TWeakObjectPtr<const AActor>> IgnoredActors;
	IgnoredActors.Add(this);
	IgnoredActors.Add(OwnerCharacter.Get());
	QueryParams.AddIgnoredActors(IgnoredActors);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_GameTraceChannel3, QueryParams);
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.0f, 0, 2.0f);
	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		
		if (HitActor)
		{
			if (AUSCombatCharacter* HitCharacter = Cast<AUSCombatCharacter>(HitActor))
			{
				UE_LOG(LogTemp, Warning, TEXT("Hit Character: %s"), *HitCharacter->GetName());
				DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 12, FColor::Green, false, 1.0f);
				// TODO : Check Damage Logic
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