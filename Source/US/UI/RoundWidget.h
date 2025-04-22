#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoundWidget.generated.h"

class UTextBlock;
class UWidgetAnimation;
class URoundManageComponent;

UCLASS()
class US_API URoundWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	void BindRoundManageComponent(URoundManageComponent* _RoundManageComponent);

private:
	UFUNCTION()
	void StartRound(int32 _CurrentRound);

	UFUNCTION()
	void UpdateNumOfEnmey(int32 _NumOfAliveEnmey, int32 _NumOfSpawnedEnemy);

private:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "MyVariable | Round ")
	TObjectPtr<UTextBlock> TextBlock_RoundStart;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "MyVariable | Round ")
	TObjectPtr<UTextBlock> TextBlock_CurrentRound;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "MyVariable | Round ")
	TObjectPtr<UTextBlock> TextBlock_NumOfEnemy;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> Animation_RoundStart;

	TWeakObjectPtr<URoundManageComponent> RoundManageComponent;
};