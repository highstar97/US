#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHub.generated.h"

class UInteractionWidget;
class UCrosshairWidget;
class UStatWidget;
class URoundWidget;
class UExpressMailBox;
class UButton;
class UImage;

UCLASS()
class US_API UMainHub : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UMainHub(const FObjectInitializer& ObjectInitializer);

    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

    virtual void NativeConstruct() override;

    FORCEINLINE UInteractionWidget* GetInteractionWidget() const { return InteractionWidget.Get(); }

    FORCEINLINE UCrosshairWidget* GetCrosshairWidget() const { return CrosshairWidget.Get(); }

    FORCEINLINE UStatWidget* GetStatWidget() const { return StatWidget.Get(); }

    FORCEINLINE URoundWidget* GetRoundWidget() const { return RoundWidget.Get(); }

    FORCEINLINE UExpressMailBox* GetExpressMailBox() const { return ExpressMailBox.Get(); }

private:
    UFUNCTION()
    void OnButtonExpressMailBoxClicked();

    UFUNCTION()
    void OnButtonExpressMailBoxHovered();

    UFUNCTION()
    void OnButtonExpressMailBoxUnhovered();

private:
    bool bIsExpressMailBoxOpened; // Is ExpressMailBox opened

    /** WBP_InteractionWidget Instance */
    UPROPERTY(VisibleInstanceOnly, Category = "MyVariable | UI ", meta = (BindWidget))
    TObjectPtr<UInteractionWidget> InteractionWidget;

    /** WBP_CrosshairWidget Instance */
    UPROPERTY(VisibleInstanceOnly, Category = "MyVariable | UI ", meta = (BindWidget))
    TObjectPtr<UCrosshairWidget> CrosshairWidget;

    /** WBP_StatWidget Instance */
    UPROPERTY(VisibleInstanceOnly, Category = "MyVariable | UI ", meta = (BindWidget))
    TObjectPtr<UStatWidget> StatWidget;

    /** WBP_RoundWidget Instance */
    UPROPERTY(VisibleInstanceOnly, Category = "MyVariable | UI ", meta = (BindWidget))
    TObjectPtr<URoundWidget> RoundWidget;

    /** WBP_ExpressMailBox Instance */
    UPROPERTY(VisibleInstanceOnly, Category = "MyVariable | UI ", meta = (BindWidget))
    TObjectPtr<UExpressMailBox> ExpressMailBox;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> Button_ExpressMailBox;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> Image_ExpressMailBox;
};