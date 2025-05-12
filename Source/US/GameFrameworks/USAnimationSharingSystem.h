#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Components/USStateComponent.h"
#include "USAnimationSharingSystem.generated.h"

class USkeletalMesh;
class USkeleton;
class USkeletalMeshComponent;

USTRUCT(BlueprintType)
struct FUSAnimationStateEntry
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EState State;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UAnimSequence> AnimSequence;
};

// AnimationSetup은 SkeletalMesh당 하나 존재
USTRUCT(BlueprintType)
struct FSkeletonAnimationSetup
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    TObjectPtr<USkeleton> Skeleton;

    UPROPERTY(EditAnywhere)
    TObjectPtr<USkeletalMesh> SkeletalMesh;

    UPROPERTY(EditAnywhere)
    TArray<FUSAnimationStateEntry> AnimationStates;

    /* 실행 중 상태별 공유 SkeletalMeshComponent */
    TMap<EState, TObjectPtr<USkeletalMeshComponent>> SharedSkeletalMeshComponents;

    UPROPERTY()
    TObjectPtr<AActor> LeaderActor;

    const FUSAnimationStateEntry* FindStateEntry(EState State) const
    {
        for (const FUSAnimationStateEntry& Entry : AnimationStates)
        {
            if (Entry.State == State)
                return &Entry;
        }
        return nullptr;
    }
};

UCLASS(Blueprintable, BlueprintType)
class US_API UUSAnimationSharingSystem : public UObject
{
	GENERATED_BODY()

public:
    void UpdateActorAnimationState(AActor* Actor, EState _State);

private:
    const FUSAnimationStateEntry* GetStateEntry(FSkeletonAnimationSetup& Setup, EState _State);

    AActor* CreateLeaderActor(FSkeletonAnimationSetup& Setup);

    USkeletalMeshComponent* GetSharedSkeletalMeshComponents(FSkeletonAnimationSetup& Setup, EState _State, const FUSAnimationStateEntry& StateEntry);

    USkeletalMeshComponent* CreateSharedSkeletalMeshComponents(FSkeletonAnimationSetup& Setup, EState _State, const FUSAnimationStateEntry& StateEntry);

    void ApplyLeaderPoseComponent(USkeletalMeshComponent* CharacterMesh, USkeletalMeshComponent* SharedSkeletalMeshComponent);

private:
    UPROPERTY(EditAnywhere, Category = "AnimationSharing")
    TArray<FSkeletonAnimationSetup> AnimationSetups;
};