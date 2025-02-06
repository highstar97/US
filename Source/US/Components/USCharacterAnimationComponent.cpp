#include "Components/USCharacterAnimationComponent.h"

#include "GameFrameworks/DataValidator.h"
#include "Characters/USCharacter.h"
#include "Characters/USCombatCharacter.h"

UUSCharacterAnimationComponent::UUSCharacterAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UUSCharacterAnimationComponent::ChangeAttackMontagePriority(EAnimationPriority _Priority)
{
    if (MontagePriorityMap.Contains(AttackMontage.Get()))
    {
        MontagePriorityMap[AttackMontage.Get()] = _Priority;
    }
}

bool UUSCharacterAnimationComponent::PlayAttackMontage()
{
    return PlayMontageWithPriority(AttackMontage.Get());
}

bool UUSCharacterAnimationComponent::PlayHitReactionMontage()
{
    int32 RandomNumber = GenerateRandomInt(0, HitReactionMontageArray.Num() - 1);

    return PlayMontageWithPriority(HitReactionMontageArray[RandomNumber].Get());
}

bool UUSCharacterAnimationComponent::PlayDeathMontage()
{
    int32 RandomNumber = GenerateRandomInt(0, DeathMontageArray.Num() - 1);

    return PlayMontageWithPriority(DeathMontageArray[RandomNumber].Get());
}

void UUSCharacterAnimationComponent::BeginPlay()
{
    Super::BeginPlay();

    if (AUSCombatCharacter* CombatCharacter = Cast<AUSCombatCharacter>(GetOwner()))
    {
        SkeletalMeshComponent = CombatCharacter->GetMesh();
        IS_VALID_OR_WARN(SkeletalMeshComponent.Get(), "SkeletalMeshComponent가 유효하지 않음.");
        
        if (IS_VALID_OR_WARN(AttackMontage.Get(), TEXT("Attack Montage가 제대로 할당되지 않음.")))
        {
            MontagePriorityMap.Emplace(AttackMontage.Get(), EAnimationPriority::Attack);
        }

        for (TObjectPtr<UAnimMontage> Montage : HitReactionMontageArray)
        {
            if (IS_VALID_OR_WARN(Montage.Get(), TEXT("Hit Reaction Montage가 제대로 할당되지 않음.")))
            {
                MontagePriorityMap.Emplace(Montage.Get(), EAnimationPriority::Hit);
            }
        }
        
        for (TObjectPtr<UAnimMontage> Montage : HitReactionMontageArray)
        {
            if (IS_VALID_OR_WARN(Montage.Get(), TEXT("Dath Montage가 제대로 할당되지 않음.")))
            {
                MontagePriorityMap.Emplace(Montage.Get(), EAnimationPriority::Death);
            }
        }
    }
}

bool UUSCharacterAnimationComponent::PlayMontageWithPriority(UAnimMontage* MontageToPlay)
{
    if (!IS_VALID_OR_WARN(MontageToPlay, TEXT("Montage가 유효하지 않음."))) return false;

    if (!IS_VALID_OR_WARN(SkeletalMeshComponent.Get(), TEXT("SkeletalMeshComponent가 유효하지 않음."))) return false;

    UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();
    if (!IS_VALID_OR_WARN(AnimInstance, TEXT("AnimInstance가 유효하지 않음."))) return false;

    if (UAnimMontage* CurrentMontage = AnimInstance->GetCurrentActiveMontage())
    {
        // 현재 실행중인 Montage의 우선순위가 더 높다면(낮은 숫자) 실행해야할 Montage는 스킵
        if (!MontagePriorityMap.Contains(CurrentMontage) || !MontagePriorityMap.Contains(MontageToPlay)) return false;
        if (MontagePriorityMap[CurrentMontage] < MontagePriorityMap[MontageToPlay]) return false;
    }
    AnimInstance->Montage_Play(MontageToPlay, 1.0f);
    return true;
}

int32 UUSCharacterAnimationComponent::GenerateRandomInt(int32 Min, int32 Max)
{
    srand(FDateTime::Now().GetMillisecond());

    return FMath::RandRange(Min, Max);
}