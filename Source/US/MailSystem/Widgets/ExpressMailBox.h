#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExpressMailBox.generated.h"

class UListView;
class UMailData;
class UMailDetail;

UCLASS()
class US_API UExpressMailBox : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	void AddExpressMailEntry(UMailData* MailData);

private:
	void SelectListViewItem(UObject* Item);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BIndWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UListView> ListView_ExpressMail;
	
	/** WBP_MailDetail Instance */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UMailDetail> MailDetail;
	
	bool bIsMailDetailOpened; // Is MailDetail opened
};