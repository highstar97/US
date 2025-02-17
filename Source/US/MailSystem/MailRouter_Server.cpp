#include "MailRouter_Server.h"

#include "GameModes/USGameMode.h"
#include "MailSystem/MailSystem.h"
#include "MailSystem/MailData.h"

#include "HAL/PlatformTime.h"

UMailRouter_Server::UMailRouter_Server()
{
	NumOfMails = 0;
	RoundRobinIndex = 0;
}

void UMailRouter_Server::Tick(float DeltaTime)
{
	int32 NumOfMailsSentInTick = 0;				// 해당 틱에서 보낸 우편의 수

	if (UserIDArray.Num() == 0) return;

	// 보낼 우편이 없거나 틱 내 처리량을 넘은 경우 Tick 종료
	while (NumOfMails > 0 && NumOfMailsSentInTick < NumOfProcessingLimits)
	{
		// 현재 RoundRobin에서 순환할 사용자 ID 가져오기
		const int32 RecipientUserID = UserIDArray[RoundRobinIndex];

		// 해당 사용자의 보내야할 우편가 있다면 메일 전송
		if (PendingMailsByUser.Contains(RecipientUserID))
		{
			TArray<TObjectPtr<UMailData>>& PendingMails = PendingMailsByUser[RecipientUserID];

			// 보낼 수 있는 메일 수 계산
			int32 NumOfMailsCanSend = FMath::Min(PendingMails.Num(), NumOfProcessingLimits - NumOfMailsSentInTick);

			// MailSystem 가져오기
			UMailSystem* MailSystem = GetMailSystemOfUser(RecipientUserID);
			if (!MailSystem)
			{
				UE_LOG(LogTemp, Warning, TEXT("[UMailRouter_Server::Tick] Failed to get MailSystem for UserID: %d"), RecipientUserID);
				AdvanceRoundRobinIndex();	// RoundRobinIndex 증가
				continue;
			}

			// 메일 전송
			MailSystem->ReceiveMailsFromRouter(TArray<TObjectPtr<UMailData>>(PendingMails.GetData(), NumOfMailsCanSend));

			// 보낸 메일 제거
			PendingMails.RemoveAt(0, NumOfMailsCanSend, true);
			NumOfMailsSentInTick += NumOfMailsCanSend;
			NumOfMails -= NumOfMailsCanSend;

			// 모든 메일을 보낸 경우, 사용자 제거
			if (PendingMails.Num() == 0)
			{
				PendingMailsByUser.Remove(RecipientUserID);
				UserIDArray.RemoveAt(RoundRobinIndex);
			}
		}
		AdvanceRoundRobinIndex();
	}
}

void UMailRouter_Server::BindGameMode(AUSGameMode* _USGameMode)
{
	if (!IsValid(_USGameMode)) return;

	USGameMode = _USGameMode;
}

void UMailRouter_Server::AddMail(UMailData* MailData)
{
	if (!MailData)
	{
		UE_LOG(LogTemp, Warning, TEXT("[UMailRouter_Server::AddMail] AddMail received nullptr MailData."));
		return;
	}

	// 새로운 수신자 추가
	if (!UserIDArray.Contains(MailData->RecipientID))
	{
		UserIDArray.Emplace(MailData->RecipientID);
	}

	if (!PendingMailsByUser.Contains(MailData->RecipientID))
	{
		PendingMailsByUser.Emplace(MailData->RecipientID);
	}

	// 해당 수신자의 대기 우편 배열에 메일 추가
	PendingMailsByUser[MailData->RecipientID].Emplace(MailData);
	++NumOfMails;
}

void UMailRouter_Server::AdvanceRoundRobinIndex()
{
	RoundRobinIndex = UserIDArray.Num() == 0 ? 0 : (UserIDArray.IsValidIndex(RoundRobinIndex) ? (RoundRobinIndex + 1) : RoundRobinIndex) % UserIDArray.Num();
}

TObjectPtr<UMailSystem> UMailRouter_Server::GetMailSystemOfUser(int32 UserID) const
{
	if (!USGameMode.IsValid() || !USGameMode.Get()->GetPlayerControllerNumberingMap().Contains(UserID))
	{
		UE_LOG(LogTemp, Warning, TEXT("[UMailRouter_Server::GetMailSystemOfUser] AddMail received nullptr MailData."));
		return nullptr;
	}

	return USGameMode.Get()->GetPlayerControllerNumberingMap()[UserID]->GetGameInstance()->GetSubsystem<UMailSystem>();
}