#include "USInteractionComponent.h"

#include "Characters/USCharacter.h"
#include "Controllers/USPlayerController.h"
#include "Interfaces/InteractionInterface.h"
#include "UI/MainHub.h"
#include "UI/InteractionWidget.h"

#include "Components/CapsuleComponent.h"

UUSInteractionComponent::UUSInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

TOptional<bool> UUSInteractionComponent::IsInteractShort() const
{ 
    if (IsValid(CurrentInteractable.GetObject()))
    {
        bool bIsShort = CurrentInteractable->InteractableData.InteractableType == EInteractableType::PRESSSHORT;
        return TOptional<bool>(bIsShort);
    }

    return TOptional<bool>();
}

void UUSInteractionComponent::InteractShort()
{
    if (IsValid(CurrentInteractable.GetObject()))
    {
        AUSPlayerController* PlayerController = Cast<AUSPlayerController>(GetOwner());
        if (PlayerController)
        {
            ACharacter* Character = PlayerController->GetCharacter();
            if (Character)
            {
                CurrentInteractable->Interact(Character);
            }
        }
    }
}

void UUSInteractionComponent::InteractLong()
{
    if (!IsValid(CurrentInteractable.GetObject())) return;

    float InteractionDuration = CurrentInteractable->InteractableData.InteractionDuration;

    AUSPlayerController* PlayerController = Cast<AUSPlayerController>(GetOwner());
    if (PlayerController)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            // 진행률 업데이트 타이머 설정
            GetWorld()->GetTimerManager().SetTimer(
                InteractionProgressHandle,
                this,
                &UUSInteractionComponent::UpdateInteractionWidget,
                0.1f,
                true
            );

            // Interact 완료 타이머 설정
            GetWorld()->GetTimerManager().SetTimer(
                InteractionTimerHandle,
                this,
                &UUSInteractionComponent::CompleteInteraction,
                InteractionDuration,
                false
            );
        }
    }
}

// TODO : StateComponent와 연계하여 Player의 움직임 감지하면 Cancel 실행되도록 하기
void UUSInteractionComponent::CancelInteraction()
{
    GetWorld()->GetTimerManager().ClearTimer(InteractionTimerHandle);
    GetWorld()->GetTimerManager().ClearTimer(InteractionProgressHandle);

    UE_LOG(LogTemp, Log, TEXT("Interaction Cancelled"));
}

// Called when the game starts
void UUSInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

    if (AUSPlayerController* PlayerController = Cast<AUSPlayerController>(GetOwner()))
    {
        if (AUSCharacter* Character = Cast<AUSCharacter>(PlayerController->GetCharacter()))
        {
            UCapsuleComponent* CapsuleComponent = Character->FindComponentByClass<UCapsuleComponent>();
            if (CapsuleComponent)
            {
                CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &UUSInteractionComponent::OnOverlapBegin);
                CapsuleComponent->OnComponentEndOverlap.AddDynamic(this, &UUSInteractionComponent::OnOverlapEnd);
            }
        }
    }
}

void UUSInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UUSInteractionComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
    {
        CurrentInteractable = OtherActor;
        ShowInteractionUI(); 
    }
}

void UUSInteractionComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && OtherActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
    {
        if (CurrentInteractable == OtherActor)
        {
            CurrentInteractable = nullptr;
            HideInteractionUI();
        }
    }
}

void UUSInteractionComponent::ShowInteractionUI()
{
    if (AUSPlayerController* PlayerController = Cast<AUSPlayerController>(GetOwner()))
    {
        if (UInteractionWidget* InteractionWidget = PlayerController->GetMainHubWidget()->GetInteractionWidget())
        {
            UE_LOG(LogTemp, Warning, TEXT("Showing Interaction UI"));
            if (InteractionWidget->GetVisibility() != ESlateVisibility::Visible)
            {
                InteractionWidget->SetVisibility(ESlateVisibility::Visible);
            }
            InteractionWidget->UpdateWidget(&CurrentInteractable->InteractableData);
        }
    }
}

void UUSInteractionComponent::HideInteractionUI()
{
    if (AUSPlayerController* PlayerController = Cast<AUSPlayerController>(GetOwner()))
    {
        if (UInteractionWidget* InteractionWidget = PlayerController->GetMainHubWidget()->GetInteractionWidget())
        {
            if (InteractionWidget->GetVisibility() == ESlateVisibility::Visible)
            {
                UE_LOG(LogTemp, Warning, TEXT("Hiding Interaction UI"));
                InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
            }
        }
    }
}

void UUSInteractionComponent::UpdateInteractionWidget()
{
    if (AUSPlayerController* PlayerController = Cast<AUSPlayerController>(GetOwner()))
    {
        if (UInteractionWidget* InteractionWidget = PlayerController->GetMainHubWidget()->GetInteractionWidget())
        {
            float RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(InteractionTimerHandle);
            float InteractionDuration = CurrentInteractable->InteractableData.InteractionDuration;
            float Progress = FMath::Clamp(1.0f - (RemainingTime / InteractionDuration), 0.0f, 1.0f);

            InteractionWidget->SetInteractionProgress(Progress);
        }
    }
}

void UUSInteractionComponent::CompleteInteraction()
{
    if (IsValid(CurrentInteractable.GetObject()))
    {
        UE_LOG(LogTemp, Log, TEXT("Interaction Completed with: %s"), *CurrentInteractable->InteractableData.Name.ToString());

        if (AUSPlayerController* PlayerController = Cast<AUSPlayerController>(GetOwner()))
        {
            if (UInteractionWidget* InteractionWidget = PlayerController->GetMainHubWidget()->GetInteractionWidget())
            {
                InteractionWidget->SetInteractionProgress(0.0f);
            }
        }
        GetWorld()->GetTimerManager().ClearTimer(InteractionProgressHandle);

        InteractShort();
    }
}