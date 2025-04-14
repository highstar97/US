#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "USGameState.generated.h"

class URoundManageComponent;
class ULevelLoadingWidget;

UCLASS()
class US_API AUSGameState : public AGameState
{
	GENERATED_BODY()

public:
	AUSGameState();

	virtual void BeginPlay() override;

	// Getter, Setter
	FORCEINLINE URoundManageComponent* GetRoundManageComponent() const { return RoundManageComponent; }

	FORCEINLINE ULevelLoadingWidget* GetLevelLoadingWidget() const { return LevelLoadingWidget.Get(); }

	void HideLevelLoadingWidget();

private:
	UPROPERTY(VisibleAnywhere, Category = "MyVariable | Component ", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<URoundManageComponent> RoundManageComponent;

	UPROPERTY(EditDefaultsOnly, Category = "MyVariable | UI | Need To Edit", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ULevelLoadingWidget> LevelLoadingWidgetClass;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable | UI ", meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<ULevelLoadingWidget> LevelLoadingWidget;
};