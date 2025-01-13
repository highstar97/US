#include "ExpressMailEntry.h"

#include "USGameMode.h"
#include "MailSystem/MailData.h"
#include "MailSystem/Widgets/MailDetail.h"

#include "Components/TextBlock.h"

void UExpressMailEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UMailData* MailData = Cast<UMailData>(ListItemObject);

	Data = MailData;
	
	UpdateTextBlock_Sender(MailData->SenderName);
	// TextBlock_RemainingDuration->SetText();
	UpdateTextBlock_Title(MailData->Title);
}

void UExpressMailEntry::UpdateTextBlock_Sender(const FString& SenderName)
{
	TextBlock_Sender.Get()->SetText(FText::FromString(SenderName));
}

void UExpressMailEntry::UpdateTextBlock_Title(const FString& Title)
{
	TextBlock_Title.Get()->SetText(FText::FromString(Title));
}