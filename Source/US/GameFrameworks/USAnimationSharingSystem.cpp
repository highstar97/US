#include "GameFrameworks/USAnimationSharingSystem.h"

#include "Components/USStateComponent.h"

#include "Components/SkeletalMeshComponent.h"

void UUSAnimationSharingSystem::UpdateActorAnimationState(AActor* Actor, EState _State)
{
    if (!IsValid(Actor)) return;

    USkeletalMeshComponent* CharacterMesh = Actor->FindComponentByClass<USkeletalMeshComponent>();
    if (!IsValid(CharacterMesh)) return;

    for (FSkeletonAnimationSetup& Setup : AnimationSetups)
    {
        // AnimationSetup에 캐릭터의 SkeletalMesh가 있는지 확인
        if (CharacterMesh->SkeletalMesh == Setup.SkeletalMesh)
        {
            // SkeletalMesh에 State가 등록되어 있는지 확인
            const FUSAnimationStateEntry* StateEntry = GetStateEntry(Setup, _State);
            if (!StateEntry) return;
            if (!StateEntry->AnimSequence) return;

            if (!IsValid(Setup.LeaderActor))
            {
                Setup.LeaderActor = CreateLeaderActor(Setup);
                if (!Setup.LeaderActor) return;    // CreateLeaderActor가 실패하여 nullptr 반환 시 종료
            }

            USkeletalMeshComponent* SharedComponent = GetSharedSkeletalMeshComponents(Setup, _State, *StateEntry);
            if (!IsValid(SharedComponent))
            {
                SharedComponent = CreateSharedSkeletalMeshComponents(Setup, _State, *StateEntry);
            }

            ApplyLeaderPoseComponent(CharacterMesh, SharedComponent);
            break;
        }
    }
}

// 특정 State에 해당하는 StateEntry를 찾는 함수
const FUSAnimationStateEntry* UUSAnimationSharingSystem::GetStateEntry(FSkeletonAnimationSetup& Setup, EState State)
{
    for (const FUSAnimationStateEntry& Entry : Setup.AnimationStates)
    {
        if (Entry.State == State)
        {
            return &Entry;
        }
    }
    return nullptr;
}

AActor* UUSAnimationSharingSystem::CreateLeaderActor(FSkeletonAnimationSetup& Setup)
{
    UWorld* World = nullptr;
    if (const UGameInstance* GI = Cast<UGameInstance>(GetOuter()))
    {
        World = GI->GetWorld();
    }
    if (!IsValid(World)) return nullptr;

    AActor* LeaderActor = World->SpawnActor<AActor>(AActor::StaticClass());
    if (!IsValid(LeaderActor)) return nullptr;

    // 위치를 State 갯수에 따라 오프셋
    FVector LocationOffset(200.0f * (Setup.SharedSkeletalMeshComponents.Num() + 1), 200.0f, 10.0f);
    LeaderActor->SetActorLocation(LocationOffset);
    LeaderActor->SetActorHiddenInGame(false);
    LeaderActor->SetFlags(RF_Transient);

    return LeaderActor;
}

USkeletalMeshComponent* UUSAnimationSharingSystem::GetSharedSkeletalMeshComponents(FSkeletonAnimationSetup& Setup, EState _State, const FUSAnimationStateEntry& StateEntry)
{
    if (TObjectPtr<USkeletalMeshComponent>* Found = Setup.SharedSkeletalMeshComponents.Find(_State))
    {
        return *Found;
    }
    return nullptr;
}

USkeletalMeshComponent* UUSAnimationSharingSystem::CreateSharedSkeletalMeshComponents(FSkeletonAnimationSetup& Setup, EState _State, const FUSAnimationStateEntry& StateEntry)
{
    USkeletalMeshComponent* SharedSkeletalMeshComponent = NewObject<USkeletalMeshComponent>(Setup.LeaderActor.Get());
    if (!IsValid(SharedSkeletalMeshComponent)) return nullptr;

    SharedSkeletalMeshComponent->SetSkeletalMesh(Setup.SkeletalMesh);
    SharedSkeletalMeshComponent->SetComponentTickEnabled(false);
    SharedSkeletalMeshComponent->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
    SharedSkeletalMeshComponent->RegisterComponent();

    if (!Setup.LeaderActor->GetRootComponent())
    {
        Setup.LeaderActor->SetRootComponent(SharedSkeletalMeshComponent);
    }
    else
    {
        SharedSkeletalMeshComponent->AttachToComponent(Setup.LeaderActor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
    }

    // 애니메이션 재생
    SharedSkeletalMeshComponent->PlayAnimation(StateEntry.AnimSequence, true);

    Setup.SharedSkeletalMeshComponents.Add(_State, SharedSkeletalMeshComponent);

    return SharedSkeletalMeshComponent;
}

// 캐릭터 Mesh에 LeaderPoseComponent를 설정
void UUSAnimationSharingSystem::ApplyLeaderPoseComponent(USkeletalMeshComponent* CharacterMesh, USkeletalMeshComponent* SharedSkeletalMeshComponent)
{
    if (!IsValid(CharacterMesh) || !IsValid(SharedSkeletalMeshComponent)) return;

    // 기존 연결 해제
    CharacterMesh->SetLeaderPoseComponent(nullptr);
    CharacterMesh->SetLeaderPoseComponent(SharedSkeletalMeshComponent);
}