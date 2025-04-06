#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RunAwayFromPlayer.generated.h"

UCLASS()
class US_API UBTTask_RunAwayFromPlayer : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_RunAwayFromPlayer();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UPROPERTY(EditAnywhere, Category = "MyVariable | AI Setting | Able To Edit")
	float FleeingDistance;
};