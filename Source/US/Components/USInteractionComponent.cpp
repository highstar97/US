#include "USInteractionComponent.h"

#include "Characters/USCharacter.h"
#include "Controllers/USPlayerController.h"
#include "Components/USStateComponent.h"
#include "Interfaces/InteractionInterface.h"
#include "UI/MainHub.h"
#include "UI/InteractionWidget.h"

#include "Components/CapsuleComponent.h"

UUSInteractionComponent::UUSInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UUSInteractionComponent::HandleInteract()
{
    if (!IsValid(OwnerController) || !IsValid(OwnerCharacter)) return;

    if (!IsValid(CurrentInteractable.GetObject()))
    {
        UE_LOG(LogTemp, Warning, TEXT("Nothing to Interact"));
        return;
    }

    if (IsReadyToInteract())
    {
        OwnerController->StopMovement();
        OwnerCharacter->GetStateComponent()->SetCurrentState(EState::INTERACTING);

        if (CurrentInteractable->InteractableData.InteractableType == EInteractableType::PRESSSHORT)
        {
            InteractShort();
        }
        else
        {
            InteractLong();
        }
    }
}

void UUSInteractionComponent::InteractShort()
{
    if (!IsValid(CurrentInteractable.GetObject()) || !IsValid(OwnerCharacter)) return;

    CurrentInteractable->Interact(OwnerCharacter);
    CurrentInteractable = nullptr;

    OwnerCharacter->GetStateComponent()->SetCurrentState(EState::IDLE);
    HideInteractionUI();
}

void UUSInteractionComponent::InteractLong()
{
    if (!IsValid(CurrentInteractable.GetObject()) || !IsValid(OwnerCharacter)) return;

    if (UWorld* World = GetWorld())
    {
        // 진행률 업데이트 타이머 설정
        World->GetTimerManager().SetTimer(
            InteractionProgressHandle,
            this,
            &UUSInteractionComponent::UpdateInteractLong,
            0.1f,
            true
        );

        // Interact 완료 타이머 설정
        World->GetTimerManager().SetTimer(
            InteractionTimerHandle,
            this,
            &UUSInteractionComponent::CompleteInteraction,
            CurrentInteractable->InteractableData.InteractionDuration,
            false
        );
    }
}

void UUSInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

    if (OwnerController = Cast<AUSPlayerController>(GetOwner()))
    {
        OwnerCharacter = Cast<AUSCharacter>(OwnerController->GetCharacter());
        if (IsValid(OwnerCharacter))
        {
            UCapsuleComponent* CapsuleComponent = OwnerCharacter->FindComponentByClass<UCapsuleComponent>();
            if (CapsuleComponent)
            {
                CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &UUSInteractionComponent::OnOverlapBegin);
                CapsuleComponent->OnComponentEndOverlap.AddDynamic(this, &UUSInteractionComponent::OnOverlapEnd);
            }
        }
    }
}

void UUSInteractionComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
    {
        IInteractionInterface* InteractionInterface = Cast<IInteractionInterface>(OtherActor);
        if (InteractionInterface)
        {
            const FInteractableData& Data = InteractionInterface->InteractableData;
            if (IsValid(Data.OwningActor))  // 이미 OwningActor가 할당되어 있다면 => 다른 캐릭터가 이미 상호작용 중
            {
                return;
            }
        }

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
    if (!IsValid(CurrentInteractable.GetObject()) || !IsValid(OwnerController)) return;

    if (UInteractionWidget* InteractionWidget = OwnerController->GetMainHubWidget()->GetInteractionWidget())
    {
        if (InteractionWidget->GetVisibility() != ESlateVisibility::Visible)
        {
            InteractionWidget->SetVisibility(ESlateVisibility::Visible);
        }
        InteractionWidget->UpdateWidget(&CurrentInteractable->InteractableData);
    }
}

void UUSInteractionComponent::HideInteractionUI()
{
    if (!IsValid(OwnerController)) return;

    if (UInteractionWidget* InteractionWidget = OwnerController->GetMainHubWidget()->GetInteractionWidget())
    {
        if (InteractionWidget->GetVisibility() == ESlateVisibility::Visible)
        {
            InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
        }
    }
}

bool UUSInteractionComponent::IsReadyToInteract()
{
    if (!IsValid(OwnerCharacter)) return false;

    switch (OwnerCharacter->GetStateComponent()->GetCurrentState())
    {
    case(EState::IDLE):
    {
        return true;
    }
    case(EState::WALKING):
    {
        return true;
    }
    case(EState::FALLING):
    {
        return false;
    }
    case(EState::INTERACTING):
    {
        return false;
    }
    default:
    {
        return false;
    }
    }
}

void UUSInteractionComponent::UpdateInteractLong()
{
    if (!IsValid(OwnerCharacter)) return;

    if (OwnerCharacter->GetStateComponent()->GetCurrentState() == EState::INTERACTING)
    {
        UpdateInteractionProgress();
    }
    else
    {
        FailedtoInteract();
    }
}

void UUSInteractionComponent::UpdateInteractionProgress()
{
    if (!IsValid(CurrentInteractable.GetObject()) || !IsValid(OwnerController)) return;

    if (UInteractionWidget* InteractionWidget = OwnerController->GetMainHubWidget()->GetInteractionWidget())
    {
        float RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(InteractionTimerHandle);
        float InteractionDuration = CurrentInteractable->InteractableData.InteractionDuration;
        float Progress = FMath::Clamp(1.0f - (RemainingTime / InteractionDuration), 0.0f, 1.0f);

        InteractionWidget->SetInteractionProgress(Progress);
    }
}

void UUSInteractionComponent::CompleteInteraction()
{
    if (!IsValid(CurrentInteractable.GetObject()) || !IsValid(OwnerController)) return;

    if (UInteractionWidget* InteractionWidget = OwnerController->GetMainHubWidget()->GetInteractionWidget())
    {
        InteractionWidget->SetInteractionProgress(0.0f);
    }

    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().ClearTimer(InteractionProgressHandle);
    }

    InteractShort();
}

void UUSInteractionComponent::FailedtoInteract()
{
    if (!IsValid(OwnerController)) return;

    if (UInteractionWidget* InteractionWidget = OwnerController->GetMainHubWidget()->GetInteractionWidget())
    {
        InteractionWidget->SetInteractionProgress(0.0f);
    }

    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().ClearTimer(InteractionTimerHandle);
        World->GetTimerManager().ClearTimer(InteractionProgressHandle);
    }
}