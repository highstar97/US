#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EnemyAppearanceInformation.generated.h"

USTRUCT(BlueprintType)
struct FEnemyAppearanceInformation : public FTableRowBase
{
    GENERATED_BODY()

public:
    FEnemyAppearanceInformation() : Round(0), Count(0), SpawnDelay(0.0f), EnemyName(""), EnemyLevel(0) {}

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 Round;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 Count;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float SpawnDelay;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FString EnemyName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 EnemyLevel;
};