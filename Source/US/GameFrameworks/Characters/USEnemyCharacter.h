#pragma once

#include "CoreMinimal.h"
#include "GameFrameworks/Characters/USCombatCharacter.h"
#include "USEnemyCharacter.generated.h"

UCLASS()
class US_API AUSEnemyCharacter : public AUSCombatCharacter
{
	GENERATED_BODY()
	
public:
	AUSEnemyCharacter(const FObjectInitializer& ObjectInitializer);
};