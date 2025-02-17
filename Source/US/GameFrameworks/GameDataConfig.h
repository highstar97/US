#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameDataConfig.generated.h"

class UDataTable;

// 게임에 필요한 데이터 테이블 들고 있는 Data Asset.
// 해당 GameDataConfig를 바꾸는 식으로 필요한 데이터에 접근할 수 있게 하려함.
UCLASS()
class US_API UGameDataConfig : public UDataAsset
{
	GENERATED_BODY()

public:
    FORCEINLINE UDataTable* GetCharacterStatTable() const { return CharacterStatTable.Get(); }

private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UDataTable> CharacterStatTable;
};