#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "USStateComponent.generated.h"

class AUSCharacter;
class UCharacterMovementComponent;

UENUM(BlueprintType)
enum class EState : uint8
{
    IDLE	    UMETA(DisplayName = "Idle"),
    WALKING     UMETA(DisplayName = "Walking"),
    FALLING     UMETA(DisplayName = "Falling"),
    INTERACTING UMETA(DisplayName = "Interacting")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class US_API UUSStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UUSStateComponent();

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void SetCurrentState(const EState NewState) { CurrentState = NewState; }

    UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
    EState GetCurrentState() const { return CurrentState; }

    bool GetIsDead() const { return bIsDead; }

    UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
    float GetSpeed() const { return Speed; }

    UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
    FVector GetVelocity() const { return Velocity; }

    void SetIsDead(const bool _bIsDead) { bIsDead = _bIsDead; }

protected:
	virtual void BeginPlay() override;

protected:
    TWeakObjectPtr<AUSCharacter> Character;

    TWeakObjectPtr<UCharacterMovementComponent> MovementComponent;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
    EState CurrentState;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
    bool bIsDead = false;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"), BlueprintGetter = GetSpeed)
    float Speed;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"), BlueprintGetter = GetVelocity)
    FVector Velocity;
};