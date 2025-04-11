#include "Components/RoundManageComponent.h"

#include "DataValidator.h"
#include "EnemyAppearanceInformation.h"
#include "EnemySpawner.h"
#include "Characters/USEnemyCharacter.h"

#include "Kismet/GameplayStatics.h"

URoundManageComponent::URoundManageComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	CurrentRound = 1;
}

void URoundManageComponent::StartRound(const int32 _Round)
{
    if (const TArray<FEnemyAppearanceInformation>* FoundRows = EnemyAppearanceInformationByRound.Find(_Round))
    {
        SpawnEnemies(*FoundRows);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No enemy data found for round %d"), _Round);
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
    for (const FEnemyAppearanceInformation& Row : TableRows_EnemyAppearanceInformation)
    {
        TSubclassOf<AUSEnemyCharacter> EnemyClass = LoadEnemyClassByName(Row.EnemyName);
        if (!EnemyClass) continue;

        for (int i = 0; i < Row.Count; ++i)
        {
            float Delay = i * Row.SpawnDelay;
            FTimerHandle TimerHandle;

            GetWorld()->GetTimerManager().SetTimer(TimerHandle, [=]()
                {
                    AEnemySpawner* Spawner = GetRandomEnemySpanwer();
                    if (Spawner)
                    {
                        Spawner->SpawnEnemy(EnemyClass, Spawner->GetActorLocation());
                    }
                }, Delay, false);
        }
    }
}

TSubclassOf<AUSEnemyCharacter> URoundManageComponent::LoadEnemyClassByName(const FString& EnemyName) const
{
    FString Path = FString::Printf(TEXT("/Game/Blueprints/Characters/BP_%s.BP_%s"), *EnemyName, *EnemyName);
    return Cast<UClass>(StaticLoadClass(AUSEnemyCharacter::StaticClass(), nullptr, *Path));
}

AEnemySpawner* URoundManageComponent::GetRandomEnemySpanwer() const
{
    if (EnemySpawners.Num() == 0) return nullptr;

    int32 Index = FMath::RandRange(0, EnemySpawners.Num() - 1);
    return EnemySpawners[Index];
}
