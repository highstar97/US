#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExpressMailBox.generated.h"

class UListView;
class UMailData;
class UMailDetail;
class UMailSystem;

UCLASS()
class US_API UExpressMailBox : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void UpdateListView();

private:
	void SelectListViewItem(UObject* Item);

	bool bIsMailDetailOpened; // Is MailDetail opened

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BIndWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UListView> ListView_ExpressMail;
	
	/** WBP_MailDetail Instance */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UMailDetail> MailDetail;
	
	UPROPERTY()
	TObjectPtr<UMailSystem> MailSystem;
};