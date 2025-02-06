#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "USCharacterAnimationComponent.generated.h"

class UAnimMontage;
class USkeletalMeshComponent;

UENUM(BlueprintType)
enum class EAnimationPriority : uint8
{
    Death = 0,
    UnInterruptedAttack = 1,
    Hit = 2,
    Attack = 3,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class US_API UUSCharacterAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UUSCharacterAnimationComponent();

    void ChangeAttackMontagePriority(EAnimationPriority _Priority);

    bool PlayAttackMontage();

    bool PlayHitReactionMontage();

    bool PlayDeathMontage();

protected:
	virtual void BeginPlay() override;

    bool PlayMontageWithPriority(UAnimMontage* MontageToPlay);

private:
    // Min <= RandomNumber <= Max
    int32 GenerateRandomInt(int32 Min, int32 Max);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UAnimMontage> AttackMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
    TArray<TObjectPtr<UAnimMontage>> HitReactionMontageArray;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
    TArray<TObjectPtr<UAnimMontage>> DeathMontageArray;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
    TMap<TObjectPtr<UAnimMontage>, EAnimationPriority> MontagePriorityMap;

    TWeakObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
};