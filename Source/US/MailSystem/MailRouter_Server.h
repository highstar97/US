#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MailRouter_Server.generated.h"

class UMailData;

// In reality, it is expected to play a role on the 'server', but in this project it is assumed to be a 'client'.
UCLASS()
class US_API UMailRouter_Server : public UObject
{
	GENERATED_BODY()
	
public:
	void AddMail(UMailData* MailData);

private:
	// Send MailData To PlayerController who has RecipientID
	UFUNCTION()
	void SendMail(UMailData* MailData);

	UPROPERTY()
	TArray<TObjectPtr<UMailData>> MailBuffer;
};