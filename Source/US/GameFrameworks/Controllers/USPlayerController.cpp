#include "USPlayerController.h"

#include "Characters/USCharacter.h"
#include "Components/USInteractionComponent.h"
#include "UI/MainHub.h"

#include "Blueprint/UserWidget.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
	
AUSPlayerController::AUSPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	// Create a InteractionComponent...
	InteractionComponent = CreateDefaultSubobject<UUSInteractionComponent>(TEXT("InteractionComponent"));
}

void AUSPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// TODO : Create Mouse Cursor Widget

	// Create MailHubWidget
	if(IsValid(MainHubWidgetClass))
	{
		MainHubWidget = CreateWidget<UMainHub>(this, MainHubWidgetClass);
		if (MainHubWidget.IsValid())
		{
			MainHubWidget.Get()->AddToViewport(0);
		}
	}
}

void AUSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AUSPlayerController::OnInteractStarted);

		// Setup move input events
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AUSPlayerController::Move);
	}
}

void AUSPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	UpdateLookToMouse(DeltaTime);
}

void AUSPlayerController::OnInteractStarted()
{
	if (!IsValid(GetInteractionComponent())) return;

	GetInteractionComponent()->HandleInteract();
}

void AUSPlayerController::Move(const FInputActionValue& Value)
{
	AUSCharacter* USCharacter = Cast<AUSCharacter>(GetCharacter());

	if (!IsValid(USCharacter)) return;

	FVector2D MoveVector = Value.Get<FVector2D>();
	USCharacter->AddMovementInput(FVector::ForwardVector, MoveVector.Y);
	USCharacter->AddMovementInput(FVector::RightVector, MoveVector.X);
}

void AUSPlayerController::UpdateLookToMouse(float DeltaTime)
{
	AUSCharacter* USCharacter = Cast<AUSCharacter>(GetCharacter());
	
	if (!IsValid(USCharacter)) return;

	FVector WorldPosition , WorldDirection;
	if (DeprojectMousePositionToWorld(WorldPosition, WorldDirection))
	{
		FVector ActorLocation = USCharacter->GetActorLocation();
		FVector TargetPoint = WorldPosition + WorldDirection * 1000.f;
		FVector LookDirection = (TargetPoint - ActorLocation).GetSafeNormal2D();
		if (!LookDirection.IsNearlyZero())
		{
			FRotator TargetRotation = LookDirection.Rotation();
			FRotator NewRotation = FMath::RInterpTo(USCharacter->GetActorRotation(), TargetRotation, DeltaTime, 10.0f);
			USCharacter->SetActorRotation(NewRotation);
		}
	}
}