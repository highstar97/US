#include "ExpressMailBox.h"

#include "MailDetail.h"
#include "../MailData.h"

#include "Components/ListView.h"

void UExpressMailBox::NativeConstruct()
{
	Super::NativeConstruct();

	bIsMailDetailOpened = false;
	MailDetail.Get()->SetVisibility(ESlateVisibility::Hidden);
	ListView_ExpressMail.Get()->OnItemClicked().AddUObject(this, &UExpressMailBox::SelectListViewItem);
}

void UExpressMailBox::AddExpressMailEntry(UMailData* MailData)
{
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