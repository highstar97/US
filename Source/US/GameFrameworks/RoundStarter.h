#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoundStarter.generated.h"

class UBoxComponent;

UCLASS()
class US_API ARoundStarter : public AActor
{
	GENERATED_BODY()

public:
	ARoundStarter();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTriggerBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	void NotifyGameModeToStartRound();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MyVariable | Component ", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "MyVariable | Collision ", meta = (PrivateAccess = "true"))
	TObjectPtr<UBoxComponent> TriggerBox;

	bool bHasStarted = false;
};