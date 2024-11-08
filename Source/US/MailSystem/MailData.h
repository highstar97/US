#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MailData.generated.h"

UENUM(BlueprintType)
enum class EMailType : uint8
{
	System UMETA(DisplayName = "System"),
	Express UMETA(DisplayName = "Express"),
	Basic UMETA(DisplayName = "Basic")
};

UCLASS(BlueprintType, Blueprintable)
class US_API UMailData : public UObject
{
	GENERATED_BODY()

public:
	UMailData() : SenderID(0), SenderName(""), RecipientID(0), RecipientName(""), Type(EMailType::Basic), Title(""), Contents(""), ItemMap() {};

	UFUNCTION(BlueprintCallable)
	void UpdateMailData(int32 NewSenderID, FString NewSenderName, int32 NewRecipientID, FString NewRecipientName, EMailType NewType, FString NewTitle, FString NewContents, TMap<TObjectPtr<UObject>, int32> NewItemMap);

	inline void UpdateRecipientName(FString NewRecipientName) { RecipientName = NewRecipientName; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mail)
	int32 SenderID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mail)
	FString SenderName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mail)
	int32 RecipientID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mail)
	FString RecipientName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mail)
	EMailType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mail)
	FString Title;

	// TODO : 시간 필요.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mail)
	FString Contents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mail)
	TMap<TObjectPtr<UObject>, int32> ItemMap;
};