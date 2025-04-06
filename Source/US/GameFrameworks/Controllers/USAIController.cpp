#include "Controllers/USAIController.h"

#include "DataValidator.h"

#include "BehaviorTree/BehaviorTree.h"

void AUSAIController::BeginPlay()
{
    Super::BeginPlay();

    if (!IS_VALID_OR_WARN(BehaviorTreeAsset, FString::Printf(TEXT("%s의 BP에서 Behavior Tree Asset이 할당되지 않음."), *GetActorLabel()))) return;

    RunBehaviorTree(BehaviorTreeAsset);
}