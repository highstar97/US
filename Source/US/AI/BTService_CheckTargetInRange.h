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

private:
	UPROPERTY(EditAnywhere, Category = "MyVariable | AI Setting | Able To Edit")
	float CheckingRadius;

	UPROPERTY(EditAnywhere, Category = "MyVariable | AI Setting | Able To Edit")
	float TargetLostThreshold;

	float TargetNotSeenDuration;
};