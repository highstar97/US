#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ProjectileDataAsset.generated.h"

UCLASS()
class US_API UProjectileDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
    /*UProjectileDataAsset() : Name("Projectile"), Mesh(nullptr), Scale(FVector::OneVector), Speed(0.0f), LifeTime(0.0f) {};

    UProjectileDataAsset(FString _Name, UStaticMesh* _Mesh, FVector _Scale, float _Speed, float _LifeTime)
        : Name(_Name), Mesh(_Mesh), Scale(_Scale), Speed(_Speed), LifeTime(_LifeTime) {};*/

    UPROPERTY(EditAnywhere)
    FString Name;

    UPROPERTY(EditAnywhere)
    UStaticMesh* Mesh;

    UPROPERTY(EditAnywhere)
    FVector Scale;

    UPROPERTY(EditAnywhere)
    float Speed;

    UPROPERTY(EditAnywhere)
    float LifeTime;
};