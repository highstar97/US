#include "USGameMode.h"

#include "Characters/USCharacter.h"
#include "Controllers/USPlayerController.h"
#include "MailSystem/MailRouter_Server.h"

#include "UObject/ConstructorHelpers.h"

AUSGameMode::AUSGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AUSPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCombatCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
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