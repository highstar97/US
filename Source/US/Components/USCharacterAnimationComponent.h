#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "USCharacterAnimationComponent.generated.h"

class UAnimMontage;
class USkeletalMeshComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class US_API UUSCharacterAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UUSCharacterAnimationComponent();

    void PlayAttackMontage();

    void PlayHitReactionMontage();

    void PlayDeathMontage();

protected:
	virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UAnimMontage> AttackMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UAnimMontage> HitReactionMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UAnimMontage> DeathMontage;

    TWeakObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
};