#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Components/USStateComponent.h"
#include "USGameInstance.generated.h"

class UUSAnimationSharingSystem;

UCLASS()
class US_API UUSGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UUSGameInstance();

	void UpdateActorAnimationState(AActor* Actor, EState NewState);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyVariable | Animation ")
	TSubclassOf<UUSAnimationSharingSystem> AnimationSharingSystemClass;

	TObjectPtr< UUSAnimationSharingSystem> AnimationSharingSystem;
};