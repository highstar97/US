#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "USPlayerController.generated.h"

class UUSInteractionComponent;
class UInputMappingContext;
class UInputAction;
class UMainHub;

UCLASS()
class AUSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AUSPlayerController();

	FORCEINLINE UUSInteractionComponent* GetInteractionComponent() const { return InteractionComponent; }

	FORCEINLINE FVector GetCrosshairLocation() const { return CrosshairLocation; }

	FORCEINLINE UMainHub* GetMainHubWidget() const { return MainHubWidget.Get(); }

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	/** Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

protected:
	virtual void SetupInputComponent() override;

	virtual void PlayerTick(float DeltaTime) override;
	
	virtual void BeginPlay();

	void OnInteractStarted();

private:
	void Move(const FInputActionValue& Value);

	void MakeCharacterLookAtCrosshair(float DeltaTime);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable | Component ", meta = (AllowPrivateAccess = "true"))
	UUSInteractionComponent* InteractionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable | UI ", meta = (AllowPrivateAccess = "true"))
	FVector CrosshairLocation;

	/** WBP_MainHub Class */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MyVariable | UI | Need To Edit", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UMainHub> MainHubWidgetClass;

	/** WBP_MailHub Instance */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable | UI ", meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<UMainHub> MainHubWidget;
};