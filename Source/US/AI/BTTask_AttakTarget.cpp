#include "AI/BTTask_AttakTarget.h"

#include "Characters/USCombatCharacter.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_AttakTarget::UBTTask_AttakTarget()
{
    NodeName = "Attack Target";
}

EBTNodeResult::Type UBTTask_AttakTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AAIController* Controller = OwnerComp.GetAIOwner();
    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
    AUSCombatCharacter* Self = Cast<AUSCombatCharacter>(Controller->GetCharacter());
    AUSCombatCharacter* Target = Cast<AUSCombatCharacter>(Blackboard->GetValueAsObject("TargetActor"));

    if (!IsValid(Self) || !IsValid(Target)) return EBTNodeResult::Failed;

    Self->Attack();

    return EBTNodeResult::Succeeded;
}