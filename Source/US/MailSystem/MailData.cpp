#include "MailData.h"

void UMailData::UpdateMailData(int32 NewSenderID, FString NewSenderName, int32 NewRecipientID, FString NewRecipientName, EMailType NewType, FString NewTitle, FString NewContents, TMap<TObjectPtr<UObject>, int32> NewItemMap)
{
	this->SenderID = NewSenderID;
	this->SenderName = NewSenderName;
	this->RecipientID = NewRecipientID;
	this->RecipientName = NewRecipientName;
	this->Type = NewType;
	this->Title = NewTitle;
	this->Contents = NewContents;
	this->ItemMap = NewItemMap;
}