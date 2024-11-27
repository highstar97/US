#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MailSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMailReceived);

class UMailData;

UCLASS(Blueprintable)
class US_API UMailSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	virtual void Deinitialize() override;

	TArray<TObjectPtr<UMailData>>& GetReceivedMails() { return ReceivedMails; }

	UFUNCTION(BlueprintCallable)
	void SendMailToRouter(UMailData* MailData);

	void ReceiveMailsFromRouter(TArray<TObjectPtr<UMailData>>&& MailDatas);

	FOnMailReceived OnMailReceived;

private:
	UPROPERTY()
	TArray<TObjectPtr<UMailData>> SentMails;

	UPROPERTY()
	TArray<TObjectPtr<UMailData>> ReceivedMails;
};