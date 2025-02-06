#include "GameFrameworks/DataValidator.h"

#include "Misc/MessageDialog.h"
#include "GenericPlatform/GenericPlatformMisc.h"

bool UDataValidator::IsValidOrWarn(UObject* DataToValidate, const FString& Message, const FString& CallerFile, int CallerLine)
{
    if (IsValid(DataToValidate)) return true;

    FString FullMessage = FString::Printf(TEXT("%s\n[Called from: %s, Line: %d]"),
        *Message,
        *CallerFile,
        CallerLine);
    FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(FullMessage));
    UE_LOG(LogTemp, Warning, TEXT("%s"), *FullMessage);
    return false;
}

bool UDataValidator::IsValidOrExit(UObject* DataToValidate, const FString& Message, const FString& CallerFile, int CallerLine)
{
    if (IsValid(DataToValidate)) return true;

    FString FullMessage = FString::Printf(TEXT("%s\n[Called from: %s, Line: %d]"),
        *Message,
        *CallerFile,
        CallerLine);
    FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(FullMessage));
    UE_LOG(LogTemp, Warning, TEXT("%s"), *FullMessage);
    FGenericPlatformMisc::RequestExit(true);
    return false;
}