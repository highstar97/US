#include "Controllers/USAIController.h"

#include "DataValidator.h"

#include "BehaviorTree/BehaviorTree.h"

void AUSAIController::BeginPlay()
{
    Super::BeginPlay();

    if (!IS_VALID_OR_EXIT(BehaviorTreeAsset, TEXT("Behavior Tree Asset이 유효하지 않음"))) return;

    RunBehaviorTree(BehaviorTreeAsset);
}