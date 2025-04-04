#include "MainHub.h"

#include "UI/InteractionWidget.h"
#include "UI/CrosshairWidget.h"
#include "MailSystem/Widgets/ExpressMailBox.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/MenuAnchor.h"
#include "Kismet/GameplayStatics.h"

UMainHub::UMainHub(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bIsExpressMailBoxOpened = false;
}

void UMainHub::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UWorld* World = GetWorld();
	if (!IsValid(World)) return;

	APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0);
	if (!IsValid(PC)) return;

	FVector2D MousePosition;
	if (PC->GetMousePosition(MousePosition.X, MousePosition.Y))
	{
		float Scale = UWidgetLayoutLibrary::GetViewportScale(this);
		FVector2D ScaledPosition = MousePosition / Scale;

		UCanvasPanelSlot* CrosshairSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(CrosshairWidget);
		if (IsValid(CrosshairSlot))
		{
			CrosshairSlot->SetPosition(ScaledPosition);
		}
	}
}

void UMainHub::NativeConstruct()
{
	Super::NativeConstruct();

	InteractionWidget.Get()->SetVisibility(ESlateVisibility::Hidden);
	ExpressMailBox.Get()->SetVisibility(ESlateVisibility::Hidden);

	// Binding Button_ExpressMailBox
	if (IsValid(Button_ExpressMailBox))
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
	if (IsValid(Image_ExpressMailBox))
	{
		Image_ExpressMailBox.Get()->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.7f));
	}
}

void UMainHub::OnButtonExpressMailBoxUnhovered()
{
	if (IsValid(Image_ExpressMailBox))
	{
		Image_ExpressMailBox.Get()->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
	}
}