#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MailSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMailReceived, UMailData*, NewMail);

class UMailData;

UCLASS(Blueprintable)
class US_API UMailSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable)
	void SendMailToRouter(UMailData* MailData);

	void ReceiveMailFromRouter(UMailData* MailData);

	FOnMailReceived OnMailReceived;

private:
	UPROPERTY()
	TArray<TObjectPtr<UMailData>> SentMails;

	UPROPERTY()
	TArray<TObjectPtr<UMailData>> ReceivedMails;
};