#include "USGameMode.h"

#include "MailSystem/MailRouter_Server.h"

#include "UObject/ConstructorHelpers.h"

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