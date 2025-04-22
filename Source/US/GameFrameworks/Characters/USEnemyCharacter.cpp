#include "Characters/USEnemyCharacter.h"

#include "GameStates/USGameState.h"
#include "Components/USCombatComponent.h"
#include "Components/USEnemyStatComponent.h"
#include "Components/RoundManageComponent.h"

#include "GameFramework/CharacterMovementComponent.h"

AUSEnemyCharacter::AUSEnemyCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UUSEnemyStatComponent>(TEXT("StatComponent")))
{
	GetCharacterMovement()->MaxWalkSpeed = 100.0f;
	
	USkeletalMeshComponent* SKMeshComponent = GetMesh();
	if (SKMeshComponent)
	{
		SKMeshComponent->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
		SKMeshComponent->bEnableUpdateRateOptimizations = true;
	}

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AUSEnemyCharacter::HandleDeath()
{
	Super::HandleDeath();

	AUSCombatCharacter* KillerCharacter = GetCombatComponent()->GetLastDamageCauser();
	if (IsValid(KillerCharacter))
	{
		float ExpReward = Cast<UUSEnemyStatComponent>(GetStatComponent())->GetExpReward();
		KillerCharacter->AddExp(ExpReward);
	}

	if (const AUSGameState* USGameState = GetWorld()->GetGameState<AUSGameState>())
	{
		if (URoundManageComponent* RoundManageComponent = USGameState->GetRoundManageComponent())
		{
			RoundManageComponent->OnEnemyDied();
		}
	}
}