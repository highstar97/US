#include "MailDetail.h"

#include "../../USGameMode.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Overlay.h"
#include "Components/ListView.h"

void UMailDetail::NativeConstruct()
{
	
}

void UMailDetail::UpdateWidget(UMailData* MailData)
{
	if (MailData)
	{
		UpdateTextBlock_Sender(MailData->SenderName);
		UpdateTextBlock_Type(MailData->Type);
		TextBlock_Title.Get()->SetText(FText::FromString(MailData->Title));
		// TextBlock_RemainingDuration.Get()->SetText(FText::FromString(MailData->)			TODO : Make MailData's variable first
		TextBlock_Content.Get()->SetText(FText::FromString(MailData->Contents));

		UpdateListView_ReceivedItem(MailData->ItemMap);
	}
}

void UMailDetail::UpdateTextBlock_Sender(FString SenderName)
{
	TextBlock_Sender.Get()->SetText(FText::FromString(SenderName));
}

void UMailDetail::UpdateTextBlock_Type(EMailType Type)
{
	FText Text = FText::GetEmpty();
	switch (Type)
	{
	case(EMailType::Basic):
	{ 
		Text = FText::FromString(FString(TEXT("일반 우편")));
		break;
	}
	case(EMailType::Express):
	{
		Text = FText::FromString(FString(TEXT("특급 우편")));
		break;
	}
	case(EMailType::System):
	{
		Text = FText::FromString(FString(TEXT("시스템 우편")));
		break;
	}
	default:
		Text = FText::FromString(FString(TEXT("Error")));
	}
	TextBlock_Type.Get()->SetText(Text);
}

void UMailDetail::UpdateListView_ReceivedItem(TMap<TObjectPtr<UObject>, int32> ItemMap)
{
	if (ItemMap.Num() > 0)
	{
		Overlay_ReceivedItems->SetVisibility(ESlateVisibility::Visible);

		for (TPair<TObjectPtr<UObject>, int32> MapData : ItemMap)
		{
			ListView_ReceivedItem.Get()->AddItem(MapData.Key);	// TODO : Update Value.
		}
	}
	else
	{
		Overlay_ReceivedItems->SetVisibility(ESlateVisibility::Hidden);
	}
}