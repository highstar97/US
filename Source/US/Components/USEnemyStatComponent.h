#pragma once

#include "CoreMinimal.h"
#include "Components/USStatComponent.h"
#include "USEnemyStatComponent.generated.h"

UCLASS()
class US_API UUSEnemyStatComponent : public UUSStatComponent
{
	GENERATED_BODY()
	
public:
	UUSEnemyStatComponent();

	FORCEINLINE float GetExpReward() const { return ExpReward; }

	void SetExpReward(const float _ExpReward);

	virtual void LoadStatsAccordingToLevel() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "MyVariable | Stat ", meta = (AllowPrivateAccess = "true"))
	float ExpReward;
};