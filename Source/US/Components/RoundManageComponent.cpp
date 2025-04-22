#include "Components/RoundManageComponent.h"

#include "DataValidator.h"
#include "EnemyAppearanceInformation.h"
#include "EnemySpawner.h"
#include "Characters/USEnemyCharacter.h"

#include "Kismet/GameplayStatics.h"

URoundManageComponent::URoundManageComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	CurrentRound = 0;
    NumOfAliveEnemy = 0;
    NumOfSpawnedEnemy = 0;
}

void URoundManageComponent::StartNextRound()
{
    int32 NextRound = CurrentRound + 1;
    if (const TArray<FEnemyAppearanceInformation>* FoundRows = EnemyAppearanceInformationByRound.Find(NextRound))
    {
        CurrentRound = NextRound;
        NumOfAliveEnemy = 0;
        NumOfSpawnedEnemy = 0;
        for (const FEnemyAppearanceInformation& Row : *FoundRows)
        {
            NumOfAliveEnemy += Row.Count;
            NumOfSpawnedEnemy += Row.Count;
        }
        SpawnEnemies(*FoundRows);

        OnRoundStarted.Broadcast(CurrentRound);
        OnUpdateNumOfEnemy.Broadcast(NumOfAliveEnemy, NumOfSpawnedEnemy);
        UE_LOG(LogTemp, Warning, TEXT("%d Round 시작!"), NextRound);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No enemy data found for round %d"), NextRound);
    }
}

void URoundManageComponent::OnEnemyDied()
{
    --NumOfAliveEnemy;
    OnUpdateNumOfEnemy.Broadcast(NumOfAliveEnemy, NumOfSpawnedEnemy);
    if (NumOfAliveEnemy <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("%d Round 종료!"), CurrentRound);
        OnRoundFinished.Broadcast();    // Delegate로 GameMode에 알림
    }
}

void URoundManageComponent::BeginPlay()
{
	Super::BeginPlay();

    if(!IS_VALID_OR_WARN(DataTable_EnemyAppearanceInformationByRound, FString::Printf(TEXT("%s의 BP에서 DataTable_EnemyAppearanceInformationByRound이 할당되지 않음."), *GetOwner()->GetActorLabel()))) return;

    TArray<FEnemyAppearanceInformation*> AllRows;
    DataTable_EnemyAppearanceInformationByRound->GetAllRows<FEnemyAppearanceInformation>(TEXT("Cache Data Table"), AllRows);

    for (const FEnemyAppearanceInformation* Row : AllRows)
    {
        if (!Row) continue;
        EnemyAppearanceInformationByRound.FindOrAdd(Row->Round).Add(*Row);
    }

    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawner::StaticClass(), FoundActors);
    
    for (AActor* Actor : FoundActors)
    {
        AEnemySpawner* EnempySpanwer = Cast<AEnemySpawner>(Actor);
        if (EnempySpanwer)
        {
            EnemySpawners.Add(EnempySpanwer);
        }
    }

    if (EnemySpawners.Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("No EnemySpawners found in the level!"));
    }
}

void URoundManageComponent::SpawnEnemies(const TArray<FEnemyAppearanceInformation>& TableRows_EnemyAppearanceInformation)
{
    for (const FEnemyAppearanceInformation& Information : TableRows_EnemyAppearanceInformation)
    {
        TSubclassOf<AUSEnemyCharacter> EnemyClass = LoadEnemyClassByName(Information.EnemyName);
        if (!EnemyClass) continue;
        
        TimerHandles.Empty();

        for (int32 i = 1; i <= Information.Count; ++i)
        {
            float Delay = i * Information.SpawnDelay;
            int32 EnemyLevel = Information.EnemyLevel;
            TimerHandles.Add(FTimerHandle());
            FTimerDelegate TimerDelegate;
            TSubclassOf<AUSEnemyCharacter> CapturedEnemyClass = EnemyClass;
            TimerDelegate.BindLambda([this, EnemyLevel, CapturedEnemyClass]()
                {
                    AEnemySpawner* Spawner = GetRandomEnemySpanwer();
                    if (Spawner)
                    {
                        Spawner->SpawnEnemy(CapturedEnemyClass, EnemyLevel, Spawner->GetActorLocation() + FVector(0.0f, 0.0f, 100.0f));
                    }
                });

            GetWorld()->GetTimerManager().SetTimer(TimerHandles[i-1], TimerDelegate, Delay, false);
        }
    }
}

TSubclassOf<AUSEnemyCharacter> URoundManageComponent::LoadEnemyClassByName(const FString& EnemyName) const
{
    FString Path = FString::Printf(TEXT("/Game/Blueprints/Characters/BP_%s.BP_%s_C"), *EnemyName, *EnemyName);
    return Cast<UClass>(StaticLoadClass(AUSEnemyCharacter::StaticClass(), nullptr, *Path));
}

AEnemySpawner* URoundManageComponent::GetRandomEnemySpanwer() const
{
    if (EnemySpawners.Num() == 0) return nullptr;

    int32 Index = FMath::RandRange(0, EnemySpawners.Num() - 1);
    return EnemySpawners[Index];
}
