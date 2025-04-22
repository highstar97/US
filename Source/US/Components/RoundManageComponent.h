#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RoundManageComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRoundStarted, int32, CurrentRound);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRoundFinished);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUpdateNumOfEnemy, int32, NumOfAliveEnemy, int32, NumOfSpawnedEnemy);

struct FEnemyAppearanceInformation;
class AUSEnemyCharacter;
class AEnemySpawner;
class UDataTable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class US_API URoundManageComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	URoundManageComponent();

	FORCEINLINE int32 GetCurrentRound() const { return CurrentRound; }

	FORCEINLINE int32 GetNumOfAliveEnemy() const { return NumOfAliveEnemy; }

	FORCEINLINE int32 GetNumOfSpawnedEnemy() const { return NumOfSpawnedEnemy; }

	void StartNextRound();

	void OnEnemyDied();

public:
	FOnRoundStarted OnRoundStarted;
	
	FOnRoundFinished OnRoundFinished;
	
	FOnUpdateNumOfEnemy OnUpdateNumOfEnemy;

protected:
	virtual void BeginPlay() override;

private:
	void SpawnEnemies(const TArray<FEnemyAppearanceInformation>& TableRows_EnemyAppearanceInformation);

	TSubclassOf<AUSEnemyCharacter> LoadEnemyClassByName(const FString& EnemyName) const;

	AEnemySpawner* GetRandomEnemySpanwer() const;

private:
	UPROPERTY(VisibleAnywhere, Category = "MyVariable | InGame ", meta = (AllowPrivateAccss = "true"))
	int32 CurrentRound;

	UPROPERTY(VisibleAnywhere, Category = "MyVariable | InGame ", meta = (AllowPrivateAccss = "true"))
	int32 NumOfAliveEnemy;
	
	UPROPERTY(VisibleAnywhere, Category = "MyVariable | InGame ", meta = (AllowPrivateAccss = "true"))
	int32 NumOfSpawnedEnemy;

	UPROPERTY(VisibleAnywhere, Category = "MyVariable | InGame ", meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<AEnemySpawner>> EnemySpawners;

	UPROPERTY(EditDefaultsOnly, Category = "MyVariable | Data Config | Need To Edit", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDataTable> DataTable_EnemyAppearanceInformationByRound;

	TArray<FTimerHandle> TimerHandles;

	TMap<int32, TArray<FEnemyAppearanceInformation>> EnemyAppearanceInformationByRound;	// 캐싱된 라운드별 적 정보
};