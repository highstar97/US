#include "USGameInstance.h"

#include "DataValidator.h"
#include "GlobalDataConfig.h"

UUSGameInstance::UUSGameInstance()
{
	
}

void UUSGameInstance::Init()
{
    Super::Init();

    IS_VALID_OR_WARN(GlobalDataConfig.Get(), TEXT("Global Data Config가 유효하지 않음."));
}