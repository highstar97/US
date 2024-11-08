#include "MailRouter_Server.h"

#include "Engine/Classes/GameFramework/PlayerState.h"
#include "../USGameMode.h"
#include "MailSystem.h"
#include "MailData.h"

void UMailRouter_Server::AddMail(UMailData* MailData)
{
	MailBuffer.Emplace(MailData);
	SendMail(MailData);
}

void UMailRouter_Server::SendMail(UMailData* MailData)
{
	if (MailData)
	{
		AUSGameMode* USGameMode = Cast<AUSGameMode>(GetOuter());
		if (USGameMode)
		{
			TObjectPtr<APlayerController> RecipientController = *(USGameMode->GetPlayerControllerNumberingMap().Find(MailData->RecipientID));
			if (RecipientController)
			{
				MailData->UpdateRecipientName(RecipientController->GetPlayerState<APlayerState>()->GetPlayerName());
				UMailSystem* MailSystem = RecipientController.Get()->GetGameInstance()->GetSubsystem<UMailSystem>();
				if (MailSystem)
				{
					MailSystem->ReceiveMailFromRouter(MailData);
				}
				return;
			}
		}
	}
}