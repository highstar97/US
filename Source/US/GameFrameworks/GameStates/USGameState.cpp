#include "GameStates/USGameState.h"

#include "DataValidator.h"
#include "UI/LevelLoadingWidget.h"

AUSGameState::AUSGameState()
{
}

void AUSGameState::BeginPlay()
{
    Super::BeginPlay();

    // 로딩 UI 인스턴스 생성
    if (IS_VALID_OR_WARN(LevelLoadingWidgetClass, FString::Printf(TEXT("%s의 BP에서 Level Loading Widget Class가 할당되지 않음."), *GetActorLabel())))
    {
        LevelLoadingWidget = CreateWidget<ULevelLoadingWidget>(GetWorld(), LevelLoadingWidgetClass);
        if (LevelLoadingWidget.IsValid())
        {
            LevelLoadingWidget->AddToViewport();
            UE_LOG(LogTemp, Warning, TEXT("Level Loading Widget Show."));
            LevelLoadingWidget->SetVisibility(ESlateVisibility::Visible);
        }
    }
}

void AUSGameState::HideLevelLoadingWidget()
{
    if (LevelLoadingWidget.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("Level Loading Widget Hide."));
        LevelLoadingWidget->SetVisibility(ESlateVisibility::Hidden);
    }
}