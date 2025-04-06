#include "AI/BTTask_MoveUntillAttackRange.h"

#include "Characters/USCombatCharacter.h"
#include "Components/USCombatComponent.h"
#include "Components/USWeaponComponent.h"
#include "Weapons/USWeapon.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_MoveUntillAttackRange::UBTTask_MoveUntillAttackRange()
{
	NodeName = "Move To Target Untill Attack Range";
    bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_MoveUntillAttackRange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AAIController* Controller = OwnerComp.GetAIOwner();
    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
    AUSCombatCharacter* Self = Cast<AUSCombatCharacter>(Controller->GetCharacter());
    AUSCombatCharacter* Target = Cast<AUSCombatCharacter>(Blackboard->GetValueAsObject("TargetActor"));
    if (!IsValid(Self) || !IsValid(Target)) return EBTNodeResult::Failed;

    float AttackRange = Self->GetCombatComponent()->GetWeaponComponent()->GetEquippedWeapon()->GetRange();

    return EBTNodeResult::InProgress;
}

void UBTTask_MoveUntillAttackRange::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    AAIController* Controller = OwnerComp.GetAIOwner();
    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
    AUSCombatCharacter* Self = Cast<AUSCombatCharacter>(Controller->GetCharacter());
    AUSCombatCharacter* Target = Cast<AUSCombatCharacter>(Blackboard->GetValueAsObject("TargetActor"));

    FVector SelfLocation = Self->GetActorLocation();
    FVector TargetLocation = Target->GetActorLocation();

    float CurrentDistance = FVector::Dist(SelfLocation, TargetLocation);
    float AttackRange = Self->GetCombatComponent()->GetWeaponComponent()->GetEquippedWeapon()->GetRange();
    const float DistanceMargin = 100.0f;
    const float DesiredDistance = AttackRange - DistanceMargin;

    // 방향 벡터 계산
    FVector ToTargetDirection = (TargetLocation - SelfLocation).GetSafeNormal();
    FVector Destination = TargetLocation - ToTargetDirection * DesiredDistance;

    if (Self->GetDistanceTo(Target) <= AttackRange)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        return;
    }

    // 이동 명령
    OwnerComp.GetAIOwner()->MoveToLocation(Destination, 5.0f);
}

void UBTTask_MoveUntillAttackRange::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
    OwnerComp.GetAIOwner()->StopMovement();
}