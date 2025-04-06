#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindPatrolLocation.generated.h"

UCLASS()
class US_API UBTTask_FindPatrolLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_FindPatrolLocation();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UPROPERTY(EditAnywhere, Category = "MyVariable | AI Setting | Able To Edit")
	float PatrolRadius;
};