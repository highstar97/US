#include "MailSystem.h"

#include "USGameMode.h"
#include "MailSystem/MailRouter_Server.h"
#include "MailSystem/MailData.h"

void UMailSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	SentMails.Empty();
	ReceivedMails.Empty();
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
		SentMails.Emplace(MailData);
	}
}

void UMailSystem::ReceiveMailsFromRouter(TArray<TObjectPtr<UMailData>>&& MailDatas)
{
	ReceivedMails.Append(MailDatas);
	OnMailReceived.Broadcast();
}