#include "USCombatCharacter.h"

#include "DataValidator.h"
#include "GameStates/USGameState.h"
#include "Components/USCombatComponent.h"
#include "Components/USStatComponent.h"
#include "Components/USStateComponent.h"
#include "Components/USWeaponComponent.h"
#include "Components/USCharacterAnimationComponent.h"
#include "UI/CharacterHealthWidget.h"

#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AUSCombatCharacter::AUSCombatCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
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

AUSWeapon* AUSCombatCharacter::GetEquippedWeapon() const
{
    if (!IsValid(CombatComponent))
    {
        UE_LOG(LogTemp, Error, TEXT("%s의 Combat Component가 유효하지 않음."), *GetOwner()->GetActorLabel());
        return nullptr;
    }

    return CombatComponent->GetEquippedWeapon();
}

void AUSCombatCharacter::EquipWeapon(AUSWeapon* NewWeapon)
{
    if (!IsValid(CombatComponent))
    {
        UE_LOG(LogTemp, Error, TEXT("%s의 Combat Component가 유효하지 않음."), *GetOwner()->GetActorLabel());
        return;
    }
    if (!NewWeapon) return;

    CombatComponent->GetWeaponComponent()->EquipWeapon(NewWeapon);
}

void AUSCombatCharacter::Attack()
{
    if (!IsValid(CombatComponent) || !IsValid(CharacterAnimationComponent)) return;

    if (CombatComponent->Attack())
    {
        // GetCharacterMovement()->StopMovementImmediately();
        CharacterAnimationComponent->PlayAttackMontage();
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
    if (!IS_VALID_OR_WARN(GetCapsuleComponent(), FString::Printf(TEXT("%s의 Capsule Compoent가 유효하지 않음."), *GetActorLabel()))) return;

    GetCapsuleComponent()->SetCollisionProfileName(IsPlayerControlled() ? TEXT("Player") : TEXT("Enemy"));
}

void AUSCombatCharacter::InitStatComponent()
{
    if (!IS_VALID_OR_WARN(StatComponent, FString::Printf(TEXT("%s의 Stat Compoent가 유효하지 않음."), *GetActorLabel()))) return;

    StatComponent->LoadStatsAccordingToLevel();
    StatComponent->OnCharacterDeath.AddDynamic(this, &AUSCombatCharacter::HandleDeath);
}

void AUSCombatCharacter::InitCharacterHealthWidgetComponent()
{
    if (!IS_VALID_OR_WARN(CharacterHealthWidgetComponent, FString::Printf(TEXT("%s의 Character Health Widget Component가 유효하지 않음."), *GetActorLabel()))) return;
    if (!IS_VALID_OR_WARN(CharacterHealthWidgetClass, FString::Printf(TEXT("%s의 BP에서 Character Health Widget Class가 할당되지 않음."), *GetActorLabel()))) return;

    CharacterHealthWidgetComponent->SetWidgetClass(CharacterHealthWidgetClass);
    UCharacterHealthWidget* CharacterHealthWidget = Cast<UCharacterHealthWidget>(CharacterHealthWidgetComponent->GetUserWidgetObject());

    if (IS_VALID_OR_WARN(CharacterHealthWidget, FString::Printf(TEXT("%s의 Character Health Widget이 유효하지 않음."), *GetActorLabel())))
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