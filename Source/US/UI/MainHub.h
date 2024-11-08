#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHub.generated.h"

class UButton;
class UImage;
class UExpressMailBox;

UCLASS()
class US_API UMainHub : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UMainHub(const FObjectInitializer& ObjectInitializer);

    virtual void NativeConstruct() override;

    inline UExpressMailBox* GetExpressMailBox() const { return ExpressMailBox.Get(); }

private:
    bool bIsExpressMailBoxOpened; // Is ExpressMailBox opened

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