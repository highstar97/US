#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "USGameMode.generated.h"

class UMailRouter_Server;

UCLASS(minimalapi)
class AUSGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AUSGameMode();

	virtual void StartPlay() override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	FORCEINLINE TMap<int32, TObjectPtr<APlayerController>> GetPlayerControllerNumberingMap() const { return PlayerControllerNumberingMap; }

	FORCEINLINE UMailRouter_Server* GetMailRouter_Server() const { return MailRouter_Server.Get(); }

	void ChangeContent(FName NewContentName);

private:
	UPROPERTY()
	int32 NumOfMap;

	UPROPERTY()
	TMap<int32, TObjectPtr<APlayerController>> PlayerControllerNumberingMap;

	UPROPERTY()
	TObjectPtr<UMailRouter_Server> MailRouter_Server;
};