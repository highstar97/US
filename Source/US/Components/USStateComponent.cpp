#include "Components/USStateComponent.h"

#include "Characters/USCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UUSStateComponent::UUSStateComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    CurrentState = EState::IDLE;
    bIsDead = false;
    Speed = 0.0f;
    Velocity = FVector::ZeroVector;
}

void UUSStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!Character.IsValid() || !MovementComponent.IsValid()) return;

    Velocity = MovementComponent->Velocity;
    Speed = Velocity.Size2D();

    if (MovementComponent.Get()->IsFalling())
    {
        CurrentState = EState::FALLING;
    }
    else if (MovementComponent.Get()->GetCurrentAcceleration().Size() > 0.0f && Speed > 0.0f)
    {
        CurrentState = EState::WALKING;
    }
    else if(CurrentState == EState::INTERACTING)
    {
        
    }
    else
    {
        CurrentState = EState::IDLE;
    }
}

void UUSStateComponent::BeginPlay()
{
	Super::BeginPlay();

    AUSCharacter* OwnerCharacter = Cast<AUSCharacter>(GetOwner());
    if (IsValid(OwnerCharacter))
    {
        Character = OwnerCharacter;
        MovementComponent = OwnerCharacter->GetCharacterMovement();
    }
}