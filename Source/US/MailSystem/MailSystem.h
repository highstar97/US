#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MailSystem.generated.h"

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
};