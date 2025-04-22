#pragma once

#include "CoreMinimal.h"
#include "Components/USStatComponent.h"
#include "USHeroStatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExpToLevelUpChanged, float, ExpToLevelUp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurrentExpChanged, float, CurrentExp);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class US_API UUSHeroStatComponent : public UUSStatComponent
{
	GENERATED_BODY()

public:
	UUSHeroStatComponent();

	FORCEINLINE float GetExpToLevelUp() const { return ExpToLevelUp; }

	FORCEINLINE float GetCurrentExp() const { return CurrentExp; }

	void SetExpToLevelUp(const float _ExpToLevelUp); 
	
	void SetCurrentExp(const float _CurrentExp);

	virtual void LoadStatsAccordingToLevel() override;

	void AddExp(const float _Exp);

public:
	FOnExpToLevelUpChanged OnExpToLevelUpChanged;

	FOnCurrentExpChanged OnCurrentExpChanged;

private:
	UPROPERTY(VisibleAnywhere, Category = "MyVariable | Stat ", meta = (AllowPrivateAccess = "true"))
	float ExpToLevelUp;

	UPROPERTY(VisibleAnywhere, Category = "MyVariable | Stat ", meta = (AllowPrivateAccess = "true"))
	float CurrentExp;
};