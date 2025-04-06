#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_SmoothFaceToTarget.generated.h"

UCLASS()
class US_API UBTService_SmoothFaceToTarget : public UBTService
{
	GENERATED_BODY()

public:
    UBTService_SmoothFaceToTarget();

protected:
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
    UPROPERTY(EditAnywhere, Category = "MyVariable | AI Setting | Able To Edit")
    float RotationSpeed;
};