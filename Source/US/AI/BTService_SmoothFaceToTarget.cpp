#include "AI/BTService_SmoothFaceToTarget.h"

#include "Characters/USCombatCharacter.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_SmoothFaceToTarget::UBTService_SmoothFaceToTarget()
{
}

void UBTService_SmoothFaceToTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AAIController* Controller = OwnerComp.GetAIOwner();
    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
    AUSCombatCharacter* Self = Cast<AUSCombatCharacter>(Controller->GetCharacter());
    AUSCombatCharacter* Target = Cast<AUSCombatCharacter>(Blackboard->GetValueAsObject("TargetActor"));
    
    if (!Self || !Target) return;

    FVector ToTarget = (Target->GetActorLocation() - Self->GetActorLocation()).GetSafeNormal2D();
    if (ToTarget.IsNearlyZero()) return;

    FRotator CurrentRotation = Self->GetActorRotation();
    FRotator ToRotation = ToTarget.Rotation();

    float NewYaw = FMath::FInterpTo(CurrentRotation.Yaw, ToRotation.Yaw, DeltaSeconds, RotationSpeed);
    FRotator NewRotation(0.f, NewYaw, 0.f);
    Self->SetActorRotation(NewRotation);
}