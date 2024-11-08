#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "USGameMode.generated.h"

class UMailRouter_Server;

UCLASS(minimalapi)
class AUSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUSGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	inline TMap<int32, TObjectPtr<APlayerController>> GetPlayerControllerNumberingMap() const { return PlayerControllerNumberingMap; }

	inline UMailRouter_Server* GetMailRouter_Server() const { return MailRouter_Server.Get(); }

private:
	UPROPERTY()
	int32 NumOfMap;

	UPROPERTY()
	TMap<int32, TObjectPtr<APlayerController>> PlayerControllerNumberingMap;

	UPROPERTY()
	TObjectPtr<UMailRouter_Server> MailRouter_Server;
};