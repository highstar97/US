#include "Components/USCharacterAnimationComponent.h"

#include "Characters/USCharacter.h"
#include "Characters/USCombatCharacter.h"

UUSCharacterAnimationComponent::UUSCharacterAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UUSCharacterAnimationComponent::PlayAttackMontage()
{
    if (!SkeletalMeshComponent.IsValid()) return;
    if (!IsValid(AttackMontage.Get())) return;

    if (UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance())
    {
        AnimInstance->Montage_Play(AttackMontage.Get(), 1.0f);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("AnimInstance not found on %s"), *GetOwner()->GetActorLabel());
    }
}

void UUSCharacterAnimationComponent::PlayHitReactionMontage()
{
    if (!SkeletalMeshComponent.IsValid()) return;
    if (!IsValid(HitReactionMontage.Get())) return;

    if (UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance())
    {
        AnimInstance->Montage_Play(HitReactionMontage.Get(), 1.0f);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("AnimInstance not found on %s"), *GetOwner()->GetActorLabel());
    }
}

void UUSCharacterAnimationComponent::PlayDeathMontage()
{
    if (!SkeletalMeshComponent.IsValid()) return;
    if (!IsValid(DeathMontage.Get())) return;

    if (UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance())
    {
        AnimInstance->Montage_Play(DeathMontage.Get(), 1.0f);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("AnimInstance not found on %s"), *GetOwner()->GetActorLabel());
    }
}

void UUSCharacterAnimationComponent::BeginPlay()
{
	Super::BeginPlay();

    if(AUSCharacter* Character = Cast<AUSCharacter>(GetOwner()))   
    {
        SkeletalMeshComponent = Character->GetMesh();
        if (!SkeletalMeshComponent.IsValid())
        {
            UE_LOG(LogTemp, Error, TEXT("SkeletalMeshComponent not found on %s"), *Character->GetActorLabel());
        }

        if (AUSCombatCharacter* CombatCharacter = Cast<AUSCombatCharacter>(Character))
        {
            if (!IsValid(AttackMontage))
            {
                UE_LOG(LogTemp, Error, TEXT("AttackMontage is not set on %s at BeginPlay!"), *CombatCharacter->GetActorLabel());
            }
        }

        if (!IsValid(HitReactionMontage))
        {
            UE_LOG(LogTemp, Error, TEXT("HitReactionMontage is not set on %s at BeginPlay!"), *Character->GetActorLabel());
        }

        if (!IsValid(DeathMontage))
        {
            UE_LOG(LogTemp, Error, TEXT("DeathMontage is not set on %s at BeginPlay!"), *Character->GetActorLabel());
        }
    }
}