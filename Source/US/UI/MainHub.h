#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHub.generated.h"

class UInteractionWidget;
class UExpressMailBox;
class UButton;
class UImage;

UCLASS()
class US_API UMainHub : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UMainHub(const FObjectInitializer& ObjectInitializer);

    virtual void NativeConstruct() override;

    FORCEINLINE UInteractionWidget* GetInteractionWidget() const { return InteractionWidget.Get(); }

    FORCEINLINE UExpressMailBox* GetExpressMailBox() const { return ExpressMailBox.Get(); }

private:
    bool bIsExpressMailBoxOpened; // Is ExpressMailBox opened

    /** WBP_InteractionWidget Instance */
    UPROPERTY(VisibleInstanceOnly, Category = UI, meta = (BindWidget))
    TObjectPtr<UInteractionWidget> InteractionWidget;

    /** WBP_ExpressMailBox Instance */
    UPROPERTY(VisibleInstanceOnly, Category = UI, meta = (BindWidget))
    TObjectPtr<UExpressMailBox> ExpressMailBox;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> Button_ExpressMailBox;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> Image_ExpressMailBox;

    UFUNCTION()
    void OnButtonExpressMailBoxClicked();

    UFUNCTION()
    void OnButtonExpressMailBoxHovered();

    UFUNCTION()
    void OnButtonExpressMailBoxUnhovered();
};