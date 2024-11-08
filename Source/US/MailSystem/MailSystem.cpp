#include "MailSystem.h"

#include "../USGameMode.h"
#include "../USPlayerController.h"
#include "MailRouter_Server.h"
#include "MailData.h"
#include "../UI/MainHub.h"
#include "Widgets/ExpressMailBox.h"

void UMailSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UMailSystem::Deinitialize()
{
	Super::Deinitialize();
}

void UMailSystem::SendMailToRouter(UMailData* MailData)
{	
	if (MailData == nullptr) return;

	TObjectPtr<UMailRouter_Server> MailRouter_Server = Cast<AUSGameMode>(GetWorld()->GetAuthGameMode())->GetMailRouter_Server();
	if (MailRouter_Server.Get())
	{
		MailRouter_Server->AddMail(MailData);
	}
}

void UMailSystem::ReceiveMailFromRouter(UMailData* MailData)
{
	AUSPlayerController* USPlayerController = Cast<AUSPlayerController>(GetWorld()->GetFirstPlayerController());
	if (USPlayerController)
	{
		if (MailData->Type == EMailType::Express)
		{
			USPlayerController->GetMainHubWidget()->GetExpressMailBox()->AddExpressMailEntry(MailData);
		}
	}
}