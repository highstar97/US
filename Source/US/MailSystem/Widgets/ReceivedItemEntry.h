#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "ReceivedItemEntry.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class US_API UReceivedItemEntry: public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Item;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_ItemName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock_ItemQuantity;
};