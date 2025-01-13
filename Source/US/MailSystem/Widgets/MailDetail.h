#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MailSystem/MailData.h"
#include "MailDetail.generated.h"

class UTextBlock;
class UButton;
class UOverlay;
class UListView;

UCLASS()
class US_API UMailDetail : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void UpdateWidget(UMailData* MailData);

private:
	void UpdateTextBlock_Sender(FString SenderName);

	void UpdateTextBlock_Type(EMailType Type);

	void UpdateListView_ReceivedItem(TMap<TObjectPtr<UObject>, int32> ItemMap);

	/* About MailDetail Widget */
	UPROPERTY(meta = (BIndWidget))
	TObjectPtr<UTextBlock> TextBlock_Sender;

	UPROPERTY(meta = (BIndWidget))
	TObjectPtr<UTextBlock> TextBlock_Type;

	UPROPERTY(meta = (BIndWidget))
	TObjectPtr<UTextBlock> TextBlock_Title;

	UPROPERTY(meta = (BIndWidget))
	TObjectPtr<UTextBlock> TextBlock_RemainingDuration;

	UPROPERTY(meta = (BIndWidget))
	TObjectPtr<UTextBlock> TextBlock_Content;

	/* About Buttons */
	UPROPERTY(meta = (BIndWidget))
	TObjectPtr<UButton> Button_ReceiveGold;

	UPROPERTY(meta = (BIndWidget))
	TObjectPtr<UButton> Button_ReceiveAll;

	UPROPERTY(meta = (BIndWidget))
	TObjectPtr<UButton> Button_DeleteMail;
	
	/* About ReceivedItems Widget */
	UPROPERTY(meta = (BIndWidget))
	TObjectPtr<UOverlay> Overlay_ReceivedItems;

	UPROPERTY(meta = (BIndWidget))
	TObjectPtr<UListView> ListView_ReceivedItem;
};