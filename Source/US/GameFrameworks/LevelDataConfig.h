#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelDataConfig.generated.h"

class UDataTable;

// 레벨에 필요한 데이터 테이블 들고 있는 Data Asset.
// 레벨마다 LevelDataAsset를 바꾸는 식으로 필요한 데이터에 접근할 수 있게 하려함.
UCLASS()
class US_API ULevelDataConfig : public UDataAsset
{
	GENERATED_BODY()

public:
    FORCEINLINE UDataTable* GetEnemyStatTable() const { return EnemyStatTable.Get(); }

private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UDataTable> EnemyStatTable;
};