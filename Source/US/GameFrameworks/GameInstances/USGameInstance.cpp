#include "USGameInstance.h"

#include "DataValidator.h"
#include "GlobalDataConfig.h"

UUSGameInstance::UUSGameInstance()
{
	
}

void UUSGameInstance::Init()
{
    Super::Init();

    if (!IS_VALID_OR_WARN(GlobalDataConfig, TEXT("BP에 Global Data Config가 할당되지 않음."))) return;
}