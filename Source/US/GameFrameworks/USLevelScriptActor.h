#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "USLevelScriptActor.generated.h"

class UProjectileDataAsset;
class AUSProjectilePool;

UCLASS()
class US_API AUSLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
public:
    AUSLevelScriptActor();

    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Pool")
    TMap<UProjectileDataAsset*, AUSProjectilePool*> PoolMap;
};