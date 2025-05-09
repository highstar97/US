#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "USAIController.generated.h"

UCLASS()
class US_API AUSAIController : public AAIController
{
	GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyVariable | Weapon | Need To Edit", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UBehaviorTree> BehaviorTreeAsset;
};