#include "AI/BTTask_FindPatrolLocation.h"

#include "Characters/USCombatCharacter.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindPatrolLocation::UBTTask_FindPatrolLocation()
{
	NodeName = "Find Patrol Location";

    PatrolRadius = 400.0f;
}

EBTNodeResult::Type UBTTask_FindPatrolLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AAIController* Controller = OwnerComp.GetAIOwner();
    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
    AUSCombatCharacter* Self = Cast<AUSCombatCharacter>(Controller->GetCharacter());

    if (!Self || !Blackboard) return EBTNodeResult::Failed;

    UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetCurrent(Self->GetWorld());
    FNavLocation NavigationLocation;

    if (NavigationSystem->GetRandomReachablePointInRadius(Self->GetActorLocation(), PatrolRadius, NavigationLocation))
    {
        Blackboard->SetValueAsVector(FName("PatrolLocation"), NavigationLocation.Location);
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}