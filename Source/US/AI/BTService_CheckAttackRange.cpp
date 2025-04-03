#include "AI/BTService_CheckAttackRange.h"

#include "Characters/USCombatCharacter.h"
#include "Components/USCombatComponent.h"
#include "Components/USWeaponComponent.h"
#include "Weapons/USWeapon.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_CheckAttackRange::UBTService_CheckAttackRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = "Check Attack Range";
}

void UBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AAIController* Controller = OwnerComp.GetAIOwner();
    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
    AUSCombatCharacter* Self = Cast<AUSCombatCharacter>(Controller->GetCharacter());
    AUSCombatCharacter* Target = Cast<AUSCombatCharacter>(Blackboard->GetValueAsObject("TargetActor"));
    float AttackRange = Self->GetCombatComponent()->GetWeaponComponent()->GetEquippedWeapon()->GetRange();

    if (!Self) return;

    if (AttackRange > 0.0f)
    {
        if (Target)
        {
            float Distance = FVector::Dist(Self->GetActorLocation(), Target->GetActorLocation());
            Blackboard->SetValueAsBool("IsInAttackRange", Distance <= AttackRange);
        }
        else
        {
            Blackboard->SetValueAsBool("IsInAttackRange", false);
        }
    }
}