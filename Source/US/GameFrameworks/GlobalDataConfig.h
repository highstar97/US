#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GlobalDataConfig.generated.h"

class UDataTable;

// 게임전역에 필요한 데이터 테이블 들고 있는 Data Asset.
UCLASS()
class US_API UGlobalDataConfig : public UDataAsset
{
	GENERATED_BODY()

public:
    FORCEINLINE UDataTable* GetCharacterStatTable() const { return CharacterStatTable.Get(); }

private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UDataTable> CharacterStatTable;
};