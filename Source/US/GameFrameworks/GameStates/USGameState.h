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
	UPROPERTY(EditAnywhere, Category = "MyVariable | Data Config | Need To Edit", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ULevelDataConfig> LevelDataConfig;

	UPROPERTY(EditDefaultsOnly, Category = "MyVariable | UI | Need To Edit", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ULevelLoadingWidget> LevelLoadingWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable | UI ", meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<ULevelLoadingWidget> LevelLoadingWidget;
};