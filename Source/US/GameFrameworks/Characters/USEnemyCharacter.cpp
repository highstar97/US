#include "Characters/USEnemyCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

AUSEnemyCharacter::AUSEnemyCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GetCharacterMovement()->MaxWalkSpeed = 100.0f;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}