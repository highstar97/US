#include "MainHub.h"

#include "../USPlayerController.h"
#include "../MailSystem/Widgets/ExpressMailBox.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/MenuAnchor.h"

UMainHub::UMainHub(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bIsExpressMailBoxOpened = false;
}

void UMainHub::NativeConstruct()
{
	Super::NativeConstruct();

	ExpressMailBox.Get()->SetVisibility(ESlateVisibility::Hidden);

	// Binding Button_ExpressMailBox
	if (Button_ExpressMailBox.Get())
	{
		Button_ExpressMailBox.Get()->OnClicked.AddDynamic(this, &UMainHub::OnButtonExpressMailBoxClicked);
		Button_ExpressMailBox.Get()->OnHovered.AddDynamic(this, &UMainHub::OnButtonExpressMailBoxHovered);
		Button_ExpressMailBox.Get()->OnUnhovered.AddDynamic(this, &UMainHub::OnButtonExpressMailBoxUnhovered);
	}
}

void UMainHub::OnButtonExpressMailBoxClicked()
{
	if (bIsExpressMailBoxOpened == true)
	{
		ExpressMailBox.Get()->SetVisibility(ESlateVisibility::Hidden);
		bIsExpressMailBoxOpened = false;
	}
	else
	{
		ExpressMailBox.Get()->SetVisibility(ESlateVisibility::Visible);
		bIsExpressMailBoxOpened = true;
	}
}

void UMainHub::OnButtonExpressMailBoxHovered()
{
	if (Image_ExpressMailBox.Get())
	{
		Image_ExpressMailBox.Get()->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.7f));
	}
}

void UMainHub::OnButtonExpressMailBoxUnhovered()
{
	if (Image_ExpressMailBox.Get())
	{
		Image_ExpressMailBox.Get()->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
	}
}
