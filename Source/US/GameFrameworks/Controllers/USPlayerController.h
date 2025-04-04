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

	void UpdateLookToMouse(float DeltaTime);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	UUSInteractionComponent* InteractionComponent;

	/** WBP_MainHub Class */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UMainHub> MainHubWidgetClass;

	/** WBP_MailHub Instance */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<UMainHub> MainHubWidget;
};