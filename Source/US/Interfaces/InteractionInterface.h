#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"

UENUM()
enum class EInteractableType : uint8
{
	PRESSSHORT UMETA(DisplayName = "PressShort"),
	PRESSLONG UMETA(DisplayName = "PressLong")
};

USTRUCT()
struct FInteractableData
{
	GENERATED_USTRUCT_BODY()

public:
	FInteractableData() : InteractableType(EInteractableType::PRESSSHORT), Name(FText::GetEmpty()), Action(FText::GetEmpty()), Quantity(0), InteractionDuration(0.0f), OwningActor(nullptr) {};

	UPROPERTY(EditInstanceOnly)
	EInteractableType InteractableType;

	UPROPERTY(EditInstanceOnly)
	FText Name;

	UPROPERTY(EditInstanceOnly)
	FText Action;

	UPROPERTY(EditInstanceOnly)
	int32 Quantity;

	UPROPERTY(EditInstanceOnly)
	float InteractionDuration;

	UPROPERTY(VisibleAnywhere)
	AActor* OwningActor;
};

UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class US_API IInteractionInterface
{
	GENERATED_BODY()

public:
	virtual void Interact(ACharacter* Interactor) = 0;

public:
	FInteractableData InteractableData;
};