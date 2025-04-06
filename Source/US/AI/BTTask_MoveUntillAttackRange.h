#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MoveUntillAttackRange.generated.h"

UCLASS()
class US_API UBTTask_MoveUntillAttackRange : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_MoveUntillAttackRange();

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};