#include "GameStates/USGameState.h"

#include "UI/LevelLoadingWidget.h"

AUSGameState::AUSGameState()
{
}

void AUSGameState::BeginPlay()
{
    Super::BeginPlay();

    // 로딩 UI 인스턴스 생성
    if (LevelLoadingWidgetClass)
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

//void AUSGameState::SetCurrentGameDataConfig(FName ContentName)
//{
//    if (LevelGameDataConfigs.Contains(ContentName))
//    {
//        CurrentGameDataConfig = LevelGameDataConfigs[ContentName];
//        UE_LOG(LogTemp, Warning, TEXT("GameDataConfig 변경됨: %s"), *CurrentGameDataConfig.GetName());
//    }
//    else
//    {
//        UE_LOG(LogTemp, Warning, TEXT("콘텐츠 %s에 해당하는 GameDataConfig가 없음!"), *ContentName.ToString());
//    }
//}

//void AUSGameState::LoadAllGameDataConfigs()
//{
//    // 애셋 레지스트리 모듈 가져오기
//    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
//
//    // 특정 폴더에서 모든 UGameDataConfig 애셋 검색
//    TArray<FAssetData> AssetDataList;
//    AssetRegistryModule.Get().GetAssetsByPath(FName("/Game/Datas/GameDataConfigs"), AssetDataList, true);
//
//    // 검색된 애셋을 TMap에 추가
//    for (const FAssetData& AssetData : AssetDataList)
//    {
//        UGameDataConfig* GameDataConfig = Cast<UGameDataConfig>(AssetData.GetAsset());
//        if (GameDataConfig)
//        {
//            FName ContentName = AssetData.AssetName;
//            GameDataConfigs.Add(ContentName, GameDataConfig);
//            UE_LOG(LogTemp, Warning, TEXT("GameDataConfig 로드됨: %s"), *ContentName.ToString());
//        }
//    }
//
//    // 기본 콘텐츠 설정 (첫 번째 애셋을 사용)
//    SetCurrentGameDataConfig("Basic");
//
//    bIsGameDataConfigLoaded = true;
//}