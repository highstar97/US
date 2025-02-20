#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "USGameInstance.generated.h"

class UGlobalDataConfig;

UCLASS()
class US_API UUSGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UUSGameInstance();

public:
    virtual void Init() override;

    FORCEINLINE UGlobalDataConfig* GetGlobalDataConfig() const { return GlobalDataConfig.Get(); }

private:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Data", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UGlobalDataConfig> GlobalDataConfig; // 글로벌 데이터 (예: 캐릭터 성장 데이터)
};