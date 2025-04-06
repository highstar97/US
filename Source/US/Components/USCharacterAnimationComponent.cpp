#include "Components/USCharacterAnimationComponent.h"

#include "DataValidator.h"
#include "Characters/USCharacter.h"
#include "Characters/USCombatCharacter.h"

UUSCharacterAnimationComponent::UUSCharacterAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UUSCharacterAnimationComponent::ChangeAttackMontagePriority(EAnimationPriority _Priority)
{
    if (MontagePriorityMap.Contains(AttackMontage))
    {
        MontagePriorityMap[AttackMontage] = _Priority;
    }
}

bool UUSCharacterAnimationComponent::PlayAttackMontage()
{
    return PlayMontageWithPriority(AttackMontage);
}

bool UUSCharacterAnimationComponent::PlayHitReactionMontage()
{
    int32 RandomNumber = GenerateRandomInt(0, HitReactionMontageArray.Num() - 1);

    return PlayMontageWithPriority(HitReactionMontageArray[RandomNumber]);
}

bool UUSCharacterAnimationComponent::PlayDeathMontage()
{
    int32 RandomNumber = GenerateRandomInt(0, DeathMontageArray.Num() - 1);

    return PlayMontageWithPriority(DeathMontageArray[RandomNumber]);
}

void UUSCharacterAnimationComponent::BeginPlay()
{
    Super::BeginPlay();

    if (AUSCombatCharacter* CombatCharacter = Cast<AUSCombatCharacter>(GetOwner()))
    {
        SkeletalMeshComponent = CombatCharacter->GetMesh();
        IS_VALID_OR_WARN(SkeletalMeshComponent.Get(), TEXT("SkeletalMeshComponent가 유효하지 않음."));
        
        if (IS_VALID_OR_WARN(AttackMontage, FString::Printf(TEXT("%s의 BP에서 Attack Montage가 할당되지 않음."), *(CombatCharacter->GetActorLabel()))))
        {
            MontagePriorityMap.Emplace(AttackMontage, EAnimationPriority::Attack);
        }

        for (TObjectPtr<UAnimMontage> Montage : HitReactionMontageArray)
        {
            if (IS_VALID_OR_WARN(Montage, FString::Printf(TEXT("%s의 BP에서 Hit Reaction Montage가 할당되지 않음."), *(CombatCharacter->GetActorLabel()))))
            {
                MontagePriorityMap.Emplace(Montage, EAnimationPriority::Hit);
            }
        }
        
        for (TObjectPtr<UAnimMontage> Montage : DeathMontageArray)
        {
            if (IS_VALID_OR_WARN(Montage, FString::Printf(TEXT("%s의 BP에서 Death Montage가 할당되지 않음."), *(CombatCharacter->GetActorLabel()))))
            {
                MontagePriorityMap.Emplace(Montage, EAnimationPriority::Death);
            }
        }
    }
}

bool UUSCharacterAnimationComponent::PlayMontageWithPriority(UAnimMontage* MontageToPlay)
{
    if (!IsValid(MontageToPlay)) return false;

    if (!IsValid(SkeletalMeshComponent.Get())) return false;

    UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();
    if (!IsValid(AnimInstance)) return false;

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