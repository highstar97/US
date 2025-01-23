#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "WeaponData.generated.h"

UENUM(BlueprintType)
enum class ERarity : uint8
{
    Common = 0		UMETA(DisplayName = "Common"),
    Uncommon = 1	UMETA(DisplayName = "Uncommon"),
    Rare = 2		UMETA(DisplayName = "Rare"),
    Epic = 3		UMETA(DisplayName = "Epic"),
    Legendary = 4	UMETA(DisplayName = "Legendary"),
    Relic = 5		UMETA(DisplayName = "Relic"),
    Ancient	= 6		UMETA(DisplayName = "Ancient")
};

USTRUCT()
struct FTextData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	FText Name;

	UPROPERTY(EditAnywhere)
	FText Description;

	UPROPERTY(EditAnywhere)
	FText Purpose;
};

USTRUCT()
struct FNumericData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	float Damage;

	UPROPERTY(EditAnywhere)
	int32 Quantity;

	UPROPERTY(EditAnywhere)
	bool bIsStackable;

	UPROPERTY(EditAnywhere)
	int32 MaxStackSize;

	UPROPERTY(EditAnywhere)
	float InteractionDuration;
};

USTRUCT()
struct FWeaponAssetData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere)
	UStaticMesh* Mesh;
};