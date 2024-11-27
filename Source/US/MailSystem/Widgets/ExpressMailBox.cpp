#include "ExpressMailBox.h"

#include "MailDetail.h"
#include "../MailSystem.h"
#include "../MailData.h"

#include "Components/ListView.h"

void UExpressMailBox::NativeConstruct()
{
	Super::NativeConstruct();

	bIsMailDetailOpened = false;
	MailDetail.Get()->SetVisibility(ESlateVisibility::Hidden);
	ListView_ExpressMail.Get()->OnItemClicked().AddUObject(this, &UExpressMailBox::SelectListViewItem);

	MailSystem = GetGameInstance()->GetSubsystem<UMailSystem>();
	if (MailSystem.Get())
	{
		MailSystem.Get()->OnMailReceived.AddDynamic(this, &UExpressMailBox::UpdateListView);
	}
}

void UExpressMailBox::UpdateListView()
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UpdateListView);
	ListView_ExpressMail.Get()->SetListItems(MailSystem.Get()->GetReceivedMails());
}

void UExpressMailBox::SelectListViewItem(UObject* Item)
{
	MailDetail.Get()->SetVisibility(ESlateVisibility::Visible);

	UMailData* MailData = Cast<UMailData>(Item);
	if (MailData)
	{
		MailDetail.Get()->UpdateWidget(MailData);
	}
}