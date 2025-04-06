#include "USPlayerController.h"

#include "DataValidator.h"
#include "Characters/USCombatCharacter.h"
#include "Components/USInteractionComponent.h"
#include "Weapons/USWeapon.h"
#include "UI/MainHub.h"

#include "Blueprint/UserWidget.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AUSPlayerController::AUSPlayerController()
{
	bShowMouseCursor = false;

	// Create a InteractionComponent...
	InteractionComponent = CreateDefaultSubobject<UUSInteractionComponent>(TEXT("InteractionComponent"));

	CrosshairLocation = FVector::ZeroVector;
}

void AUSPlayerController::BeginPlay()
{ 
	Super::BeginPlay();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Create MainHubWidget
	if (IS_VALID_OR_WARN(MainHubWidgetClass, FString::Printf(TEXT("%s의 BP에서 Main Hub Widget Class가 할당되지 않음."), *GetActorLabel())))
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
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AUSPlayerController::Move);
	}
}

void AUSPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	MakeCharacterLookAtCrosshair(DeltaTime);
}

void AUSPlayerController::OnInteractStarted()
{
	if (!IsValid(GetInteractionComponent())) return;

	GetInteractionComponent()->HandleInteract();
}

void AUSPlayerController::Move(const FInputActionValue& Value)
{
	AUSCombatCharacter* CombatCharacter = Cast<AUSCombatCharacter>(GetCharacter());

	if (!IsValid(CombatCharacter)) return;

	FVector2D MoveVector = Value.Get<FVector2D>();
	CombatCharacter->AddMovementInput(FVector::ForwardVector, MoveVector.Y);
	CombatCharacter->AddMovementInput(FVector::RightVector, MoveVector.X);
}

void AUSPlayerController::MakeCharacterLookAtCrosshair(float DeltaTime)
{
	AUSCombatCharacter* CombatCharacter = Cast<AUSCombatCharacter>(GetCharacter());
	if (!IsValid(CombatCharacter)) return;

	FVector MuzzleLocation;
	AUSWeapon* EquippedWeapon = CombatCharacter->GetEquippedWeapon();
	if (IsValid(EquippedWeapon))
	{
		MuzzleLocation = EquippedWeapon->GetMuzzleLocation();
	}
	else
	{
		MuzzleLocation = CombatCharacter->GetActorLocation();
	}

	FVector WorldPosition, WorldDirection;
	if (DeprojectMousePositionToWorld(WorldPosition, WorldDirection))
	{
		// Line Trace 세팅
		FVector TraceStart = WorldPosition;
		FVector TraceEnd = TraceStart + (WorldDirection * 10000.f);

		FHitResult HitResult;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(CombatCharacter);

		// Line Trace
		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, Params);

		if (bHit)
		{
			// Crosshair 위치 저장
			CrosshairLocation = HitResult.ImpactPoint;
			CrosshairLocation.Z = MuzzleLocation.Z;

			FVector TargetLocation = HitResult.ImpactPoint;
			FVector CharacterLocation = CombatCharacter->GetActorLocation();

			// Yaw 회전만 고려 (Z 높이는 무시)
			FVector DirectionToLook = (TargetLocation - CharacterLocation);
			DirectionToLook.Z = 0.f;

			if (!DirectionToLook.IsNearlyZero())
			{
				FRotator TargetRotation = DirectionToLook.Rotation();
				FRotator CurrentRotation = CombatCharacter->GetActorRotation();
				FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, 10.f);
				CombatCharacter->SetActorRotation(NewRotation);
			}
		}
	}
}