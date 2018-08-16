// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATankPawn;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ATankPlayerController();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	ATankPawn* GetControlledTank();

	// Start the tank moving the barrel towards the cross hair.
	void AimAtCrosshair();

	bool GetSightRayHitLocation(FVector& endLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CrossHair")
	float m_CrossHairXLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CrossHair")
	float m_CrossHairYLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CrossHair")
	float m_LineTraceRange;

private:
		
	ATankPawn* m_pTankPawn;
	
};