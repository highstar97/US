#include "Characters/USEnemyCharacter.h"

#include "GameStates/USGameState.h"
#include "Components/RoundManageComponent.h"

#include "GameFramework/CharacterMovementComponent.h"

AUSEnemyCharacter::AUSEnemyCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GetCharacterMovement()->MaxWalkSpeed = 100.0f;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AUSEnemyCharacter::HandleDeath()
{
	Super::HandleDeath();

	if (const AUSGameState* USGameState = GetWorld()->GetGameState<AUSGameState>())
	{
		if (URoundManageComponent* RoundManageComponent = USGameState->GetRoundManageComponent())
		{
			RoundManageComponent->OnEnemyDied();
		}
	}
}