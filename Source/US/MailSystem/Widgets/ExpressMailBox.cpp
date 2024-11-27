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

	UMailSystem* MailSystem = GetGameInstance()->GetSubsystem<UMailSystem>();
	if (MailSystem)
	{
		MailSystem->OnMailReceived.AddDynamic(this, &UExpressMailBox::AddExpressMailEntry);
	}
}

void UExpressMailBox::AddExpressMailEntry(UMailData* MailData)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(AddExpressMailEntry);
	ListView_ExpressMail.Get()->AddItem(MailData);
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