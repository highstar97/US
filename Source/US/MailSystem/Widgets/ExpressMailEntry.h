#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "ExpressMailEntry.generated.h"

class UMailData;
class UImage;
class UTextBlock;

UCLASS()
class US_API UExpressMailEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

private:
	void UpdateTextBlock_Sender(const FString& SenderName);

	void UpdateTextBlock_Title(const FString& Title);

	UPROPERTY(VisibleAnywhere, Category = Data)
	TObjectPtr<UMailData> Data;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Type;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_Sender;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_RemainingDuration;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_Title;
};