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
    // 현재 시간을 시드로한 랜덤 Int 생성, (Min <= RandomNumber <= Max)
    int32 GenerateRandomInt(int32 Min, int32 Max);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyVariable | Animation | Need To Edit", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UAnimMontage> AttackMontage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyVariable | Animation | Need To Edit", meta = (AllowPrivateAccess = "true"))
    TArray<TObjectPtr<UAnimMontage>> HitReactionMontageArray;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyVariable | Animation | Need To Edit", meta = (AllowPrivateAccess = "true"))
    TArray<TObjectPtr<UAnimMontage>> DeathMontageArray;

    UPROPERTY()
    TMap<TObjectPtr<UAnimMontage>, EAnimationPriority> MontagePriorityMap;

    TWeakObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
};