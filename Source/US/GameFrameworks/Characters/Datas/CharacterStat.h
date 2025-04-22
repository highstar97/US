#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CharacterStat.generated.h"

USTRUCT(BlueprintType)
struct FCharacterStat : public FTableRowBase
{
    GENERATED_BODY()

public:
    FCharacterStat() : Level(1), MaxHealth(100.0f), Attack(10.0f), Defense(5.0f), AttackSpeed(0.5f) {}

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable | Stat ")
    int32 Level;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable | Stat ")
    float MaxHealth;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable | Stat ")
    float Attack;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable | Stat ")
    float Defense;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable | Stat ")
    float AttackSpeed;
};

USTRUCT(BlueprintType)
struct FHeroStat : public FCharacterStat
{
    GENERATED_BODY()

public:
    FHeroStat() : ExpToLevelUp(100.0f) {}

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable | Stat ")
    float ExpToLevelUp;
};

USTRUCT(BlueprintType)
struct FEnemyStat : public FCharacterStat
{
    GENERATED_BODY()

public:
    FEnemyStat() : ExpReward(50.0f) {}

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable | Stat ")
    float ExpReward;
};