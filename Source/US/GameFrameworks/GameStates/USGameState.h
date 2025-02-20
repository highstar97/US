#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "USGameState.generated.h"

class ULevelDataConfig;
class ULevelLoadingWidget;

UCLASS()
class US_API AUSGameState : public AGameState
{
	GENERATED_BODY()

public:
	AUSGameState();

	virtual void BeginPlay() override;

	// Getter, Setter
	FORCEINLINE ULevelDataConfig* GetLevelDataConfig() const { return LevelDataConfig.Get(); }

	FORCEINLINE ULevelLoadingWidget* GetLevelLoadingWidget() const { return LevelLoadingWidget.Get(); }

	void HideLevelLoadingWidget();

private:
	UPROPERTY(EditAnywhere, Category = "Game Config", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ULevelDataConfig> LevelDataConfig;

	UPROPERTY(EditDefaultsOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ULevelLoadingWidget> LevelLoadingWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<ULevelLoadingWidget> LevelLoadingWidget;
};