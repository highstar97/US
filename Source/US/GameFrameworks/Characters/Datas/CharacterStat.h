#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CharacterStat.generated.h"

USTRUCT(BlueprintType)
struct FCharacterStat : public FTableRowBase
{
    GENERATED_BODY()

public:
    FCharacterStat() : Level(1), MaxHealth(100.0f), Attack(10.0f), Defense(5.0f) {}

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
    int32 Level;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
    float MaxHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
    float Attack;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
    float Defense;
};