#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_AttakTarget.generated.h"

UCLASS()
class US_API UBTTask_AttakTarget : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_AttakTarget();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};