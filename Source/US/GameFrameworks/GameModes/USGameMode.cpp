#include "USGameMode.h"

#include "GameStates/USGameState.h"
#include "Components/RoundManageComponent.h"
#include "RoundStarter.h"
#include "MailSystem/MailRouter_Server.h"

#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AUSGameMode::AUSGameMode()
{

}

void AUSGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	PlayerControllerNumberingMap.Emplace(NumOfMap, NewPlayer);

	FString NewName("USPlayer_");
	NewName.Append(FString::FromInt(NumOfMap++));
	ChangeName(NewPlayer, NewName, false);
}

void AUSGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	NumOfMap = 0;

	MailRouter_Server = NewObject<UMailRouter_Server>(this);
	MailRouter_Server->BindGameMode(this);
}

void AUSGameMode::StartRound()
{
	AUSGameState* USGameState = GetGameState<AUSGameState>();
	URoundManageComponent* RoundManageComponent = USGameState->GetRoundManageComponent();
	if (!IsValid(RoundManageComponent)) return;

	RoundManageComponent->OnRoundFinished.RemoveDynamic(this, &AUSGameMode::FinishRound);
	RoundManageComponent->OnRoundFinished.AddDynamic(this, &AUSGameMode::FinishRound);

	RoundManageComponent->StartNextRound();
}

void AUSGameMode::FinishRound()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARoundStarter::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		if (ARoundStarter* RoundStarter = Cast<ARoundStarter>(Actor))
		{
			RoundStarter->SetActorHiddenInGame(false);
			RoundStarter->SetActorEnableCollision(true);
		}
	}
}