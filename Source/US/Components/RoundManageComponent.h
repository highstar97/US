#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RoundManageComponent.generated.h"

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

	void StartRound(const int32 _Round);

protected:
	virtual void BeginPlay() override;

private:
	void SpawnEnemies(const TArray<FEnemyAppearanceInformation>& TableRows_EnemyAppearanceInformation);

	TSubclassOf<AUSEnemyCharacter> LoadEnemyClassByName(const FString& EnemyName) const;

	AEnemySpawner* GetRandomEnemySpanwer() const;

private:
	UPROPERTY(VisibleAnywhere, Category = "MyVariable | InGame ", meta = (AllowPrivateAccss = "true"))
	int32 CurrentRound;

	UPROPERTY(VisibleAnywhere, Category = "MyVariable | InGame ", meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<AEnemySpawner>> EnemySpawners;

	UPROPERTY(EditDefaultsOnly, Category = "MyVariable | Data Config | Need To Edit", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDataTable> DataTable_EnemyAppearanceInformationByRound;

	TMap<int32, TArray<FEnemyAppearanceInformation>> EnemyAppearanceInformationByRound;	// 캐싱된 라운드별 적 정보
};