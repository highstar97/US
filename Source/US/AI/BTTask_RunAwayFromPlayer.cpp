#include "AI/BTTask_RunAwayFromPlayer.h"

#include "Characters/USCombatCharacter.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_RunAwayFromPlayer::UBTTask_RunAwayFromPlayer()
{
	NodeName = "Run Away From Player";
    FleeingDistance = 1000.0f;
}

EBTNodeResult::Type UBTTask_RunAwayFromPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AAIController* Controller = OwnerComp.GetAIOwner();
    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
    AUSCombatCharacter* Self = Cast<AUSCombatCharacter>(Controller->GetCharacter());
    AUSCombatCharacter* Target = Cast<AUSCombatCharacter>(Blackboard->GetValueAsObject("TargetActor"));

    if (!IsValid(Self) || !IsValid(Target)) return EBTNodeResult::Failed;

    FVector AwayFromPlayerDirection = (Self->GetActorLocation() - Target->GetActorLocation()).GetSafeNormal();
    FVector FleeDestination = Self->GetActorLocation() + AwayFromPlayerDirection * FleeingDistance;

    Controller->MoveToLocation(FleeDestination);
    return EBTNodeResult::Succeeded;
}