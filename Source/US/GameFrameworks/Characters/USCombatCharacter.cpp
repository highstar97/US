#include "USCombatCharacter.h"

#include "DataValidator.h"
#include "GameStates/USGameState.h"
#include "Controllers/USPlayerController.h"
#include "Components/USCombatComponent.h"
#include "Components/USStatComponent.h"
#include "Components/USStateComponent.h"
#include "Components/USCharacterAnimationComponent.h"
#include "UI/CharacterHealthWidget.h"

#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AUSCombatCharacter::AUSCombatCharacter()
{
    CombatComponent = CreateDefaultSubobject<UUSCombatComponent>(TEXT("CombatComponent"));

    StatComponent = CreateDefaultSubobject<UUSStatComponent>(TEXT("StatComponent"));

    CharacterHealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("CharacterHealthWidgetComponent"));

    CharacterHealthWidgetComponent->SetupAttachment(RootComponent);
    CharacterHealthWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 120.0f));
    CharacterHealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
    CharacterHealthWidgetComponent->SetDrawSize(FVector2D(100.0f, 10.0f));
    CharacterHealthWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AUSCombatCharacter::BeginPlay()
{
    Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimerForNextTick(this, &AUSCombatCharacter::DelayedBeginPlay);
}

void AUSCombatCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    AUSPlayerController* PlayerController = Cast<AUSPlayerController>(GetController());
    if (IsValid(PlayerController))
    {
        UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
        if (IsValid(EnhancedInputComponent) && IsValid(PlayerController->AttackAction))
        {
            EnhancedInputComponent->BindAction(PlayerController->AttackAction, ETriggerEvent::Started, this, &AUSCombatCharacter::Attack);
        }
    }
}

void AUSCombatCharacter::DelayedBeginPlay()
{
    if (UWorld* World = GetWorld())
    {
        AUSGameState* USGameState = World->GetGameState<AUSGameState>();
        if (IsValid(USGameState))
        {
            InitCapsuleCollision();
            InitStatComponent();
            InitCharacterHealthWidgetComponent();
            USGameState->HideLevelLoadingWidget();
        }
        else
        {
            GetWorld()->GetTimerManager().SetTimerForNextTick(this, &AUSCombatCharacter::DelayedBeginPlay);
        }
    }
}

void AUSCombatCharacter::InitCapsuleCollision()
{
    if (!IS_VALID_OR_EXIT(GetCapsuleComponent(), TEXT("Capsule Compoent가 유효하지 않음."))) return;

    GetCapsuleComponent()->SetCollisionProfileName(IsPlayerControlled() ? TEXT("Player") : TEXT("Enemy"));
}

void AUSCombatCharacter::InitStatComponent()
{
    if (!IS_VALID_OR_EXIT(StatComponent, TEXT("Stat Component가 유효하지 않음."))) return;

    StatComponent->LoadStatsAccordingToLevel();
    StatComponent->OnCharacterDeath.AddDynamic(this, &AUSCombatCharacter::HandleDeath);
}

void AUSCombatCharacter::InitCharacterHealthWidgetComponent()
{
    if (!IS_VALID_OR_EXIT(CharacterHealthWidgetComponent, TEXT("Character Health Widget Component가 유효하지 않음."))) return;
    if (!IS_VALID_OR_EXIT(CharacterHealthWidgetClass, TEXT("Character Health Widget Class가 유효하지 않음."))) return;

    CharacterHealthWidgetComponent->SetWidgetClass(CharacterHealthWidgetClass);
    UCharacterHealthWidget* CharacterHealthWidget = Cast<UCharacterHealthWidget>(CharacterHealthWidgetComponent->GetUserWidgetObject());

    if (IS_VALID_OR_WARN(CharacterHealthWidget, TEXT("Character Health Widget이 유효하지 않음.")))
    {
        CharacterHealthWidget->BindCharacterStat(StatComponent);
    }
}

void AUSCombatCharacter::HandleDeath()
{
    if (!IsValid(StateComponent) ||!IsValid(CharacterAnimationComponent)) return;

    if (StateComponent->GetIsDead()) return;

    StateComponent->SetIsDead(true);

    DetachFromControllerPendingDestroy();
    GetCharacterAnimationComponent()->PlayDeathMontage();

    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    SetLifeSpan(1.0f);
}

float AUSCombatCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

    if (!IsValid(StatComponent)) return 0.0f;
    
    // TODO : this(Character)에 버프 혹은 디버프가 있다면 미리 처리

    float FinalDamage = DamageAmount;

    StatComponent->TakeDamage(FinalDamage);

    return FinalDamage;
}

void AUSCombatCharacter::Attack()
{
    if (!IsValid(CombatComponent) || !IsValid(CharacterAnimationComponent)) return;

    TOptional<bool> IsWeaponEquippedQueryResult = CombatComponent->GetIsWeaponEquipped();
    if (IsWeaponEquippedQueryResult.IsSet() && IsWeaponEquippedQueryResult.GetValue())
    {
        if (CharacterAnimationComponent->PlayAttackMontage())
        {
            GetCharacterMovement()->StopMovementImmediately();
        }
    }
}