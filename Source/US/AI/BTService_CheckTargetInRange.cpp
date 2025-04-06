#include "AI/BTService_CheckTargetInRange.h"

#include "Characters/USCombatCharacter.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_CheckTargetInRange::UBTService_CheckTargetInRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = "Check Target In Range";

    CheckingRadius = 700.0f;
	TargetLostThreshold = 5.0f;
	TargetNotSeenDuration = 0.0f;
}

void UBTService_CheckTargetInRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AAIController* Controller = OwnerComp.GetAIOwner();
    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
    AUSCombatCharacter* Self = Cast<AUSCombatCharacter>(Controller->GetCharacter());
	
	if (!IsValid(Self)) return;

	UWorld* World = Self->GetWorld();
	FVector Center = Self->GetActorLocation();

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, Self);
	bool bResult = GetWorld()->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,		// ECC_GameTraceChannel1 is 'Player' (ECC_GameTraceChannel2 is 'Enemy')
		FCollisionShape::MakeSphere(CheckingRadius),
		CollisionQueryParam
	);

	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			AUSCombatCharacter* TargetActor = Cast<AUSCombatCharacter>(OverlapResult.GetActor());
			if(IsValid(TargetActor))
			{
				Blackboard->SetValueAsBool("IsTargetVisible", true);
				Blackboard->SetValueAsObject("TargetActor", TargetActor);
				Blackboard->SetValueAsVector("LastKnownLocation", TargetActor->GetActorLocation());

				TargetNotSeenDuration = 0.0f;

				DrawDebugSphere(World, Center, CheckingRadius, 16, FColor::Green, false, 0.2f);
				DrawDebugPoint(World, TargetActor->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
				return;
			}
		}
	}

	DrawDebugSphere(World, Center, CheckingRadius, 16, FColor::Red, false, 0.2f);
	
	TargetNotSeenDuration += DeltaSeconds;

	if (TargetNotSeenDuration >= TargetLostThreshold)
	{
		Blackboard->SetValueAsBool("IsTargetVisible", false);
		Blackboard->ClearValue("TargetActor");
	}
}