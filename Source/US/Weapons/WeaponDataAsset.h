#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Weapons/WeaponData.h"
#include "WeaponDataAsset.generated.h"

UCLASS()
class US_API UWeaponDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Weapon Data")
	FName ID;

	UPROPERTY(EditAnywhere, Category = "Weapon Data")
	ERarity Rarity;

	UPROPERTY(EditAnywhere, Category = "Weapon Data")
	FTextData TextData;

	UPROPERTY(EditAnywhere, Category = "Weapon Data")
	FNumericData NumericData;

	UPROPERTY(EditAnywhere, Category = "Weapon Data")
	FWeaponAssetData AssetData;
};