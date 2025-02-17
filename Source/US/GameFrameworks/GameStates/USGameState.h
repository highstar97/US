#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Engine/DataTable.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "USGameState.generated.h"

class UGameDataConfig;

UCLASS()
class US_API AUSGameState : public AGameState
{
	GENERATED_BODY()

public:
	AUSGameState();

	virtual void BeginPlay() override;

	// Getter, Setter

	FORCEINLINE TMap<FName, TObjectPtr<UGameDataConfig>> GetGameDataConfigs() const { return GameDataConfigs; }

	FORCEINLINE UGameDataConfig* GetCurrentGameDataConfig() const { return CurrentGameDataConfig.Get(); }

	void SetCurrentGameDataConfig(FName ContentName);

	// Functions
	
	// Asset Registry Module을 이용하여 게임에 필요한 모든 GameDataConfigs 가져오기.
	void LoadAllGameDataConfigs();

	bool bIsGameDataConfigReady = false;

private:
	// Contents별 GameDataConfig 모음
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameConfig, meta = (AllowPrivateAccess = "true"))
	TMap<FName, TObjectPtr<UGameDataConfig>> GameDataConfigs;

	// 현재 Content의 GameDataConfig
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameConfig, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UGameDataConfig> CurrentGameDataConfig;
};