#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataValidator.generated.h"

UCLASS()
class US_API UDataValidator : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
    
    UFUNCTION(BlueprintCallable, Category = "Validation")
    static bool IsValidOrWarn(UObject* DataToValidate, const FString& Message, const FString& CallerFile, int CallerLine);
   
    UFUNCTION(BlueprintCallable, Category = "Validation")
    static bool IsValidOrExit(UObject* DataToValidate, const FString& Message, const FString& CallerFile, int CallerLine);
};

// [리턴 bool] IsValid 체크 및 실패 시 Warning 창 생성
#define IS_VALID_OR_WARN(Data, Msg) UDataValidator::IsValidOrWarn(Data, Msg, __FILE__, __LINE__) 

// [리턴 bool] IsValid 체크 및 실패 시 Error 창 생성 및 게임 종료
#define IS_VALID_OR_EXIT(Data, Msg) UDataValidator::IsValidOrExit(Data, Msg, __FILE__, __LINE__)