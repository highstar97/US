#include "ExpressMailEntry.h"

#include "../../USGameMode.h"
#include "../MailData.h"
#include "MailDetail.h"

#include "Components/TextBlock.h"

void UExpressMailEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UMailData* MailData = Cast<UMailData>(ListItemObject);

	Data = MailData;
	
	UpdateTextBlock_Sender(MailData->SenderName);
	// TextBlock_RemainingDuration->SetText();
	TextBlock_Title.Get()->SetText(FText::FromString(MailData->Title));
}

void UExpressMailEntry::UpdateTextBlock_Sender(FString SenderName)
{
	TextBlock_Sender.Get()->SetText(FText::FromString(SenderName));
}