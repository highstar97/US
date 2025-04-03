#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CheckTargetInRange.generated.h"

UCLASS()
class US_API UBTService_CheckTargetInRange : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_CheckTargetInRange();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere)
	float CheckingRadius;

	UPROPERTY(EditAnywhere)
	float ForgetTime;

	float NotSeenDuration = 0.0f;
};