#pragma once

#include "CoreMinimal.h"
#include "Tickable.h"
#include "UObject/NoExportTypes.h"
#include "MailRouter_Server.generated.h"

class UMailData;
class UMailSystem;
class AUSGameMode;

// In reality, it is expected to play a role on the 'server', but in this project it is assumed to be a 'client'.
UCLASS()
class US_API UMailRouter_Server : public UObject, public FTickableGameObject
{
	GENERATED_BODY()
	
public:
	UMailRouter_Server();
	
	virtual void Tick(float DeltaTime) override;

	virtual TStatId GetStatId() const override
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(UMailRouter_Server, STATGROUP_Tickables);
	}

	void AddMail(UMailData* MailData);

	void AdvanceRoundRobinIndex();

	TObjectPtr<UMailSystem> GetMailSystemOfUser(int32 UserID) const;

private:
	const int32 NumOfProcessingLimits = 10000;	// 처리량 제한 크기

	int32 NumOfMails;		// MailRouter에 존재하는 Mail의 수

	int32 RoundRobinIndex;	// 현재 우편을 전송할 차례의 UserID를 가리킴

	UPROPERTY()
	TObjectPtr<AUSGameMode> USGameMode;

	TArray<int32> UserIDArray;

	TMap<int32, TArray<TObjectPtr<UMailData>>> PendingMailsByUser; // Key : UserID, Value : MailData Array
};