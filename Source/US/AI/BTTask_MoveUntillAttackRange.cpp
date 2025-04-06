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
}

void UBTTask_MoveUntillAttackRange::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    AAIController* Controller = OwnerComp.GetAIOwner();
    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
    AUSCombatCharacter* Self = Cast<AUSCombatCharacter>(Controller->GetCharacter());
    AUSCombatCharacter* Target = Cast<AUSCombatCharacter>(Blackboard->GetValueAsObject("TargetActor"));

    if (!IsValid(Self) || !IsValid(Target))
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    float Distance = Self->GetDistanceTo(Target);
    float AttackRange = Self->GetCombatComponent()->GetWeaponComponent()->GetEquippedWeapon()->GetRange();

    if (Distance <= AttackRange)
    {
        Controller->StopMovement();
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
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
    Controller->MoveToActor(Target, AttackRange - 50.f);

    return EBTNodeResult::Succeeded;
}