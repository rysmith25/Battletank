// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATankPawn;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	
	ATankAIController();

	virtual void BeginPlay() override;

	ATankPawn* GetAITankPawn();

	ATankPawn* GetPlayerTankPawn();

private:

	ATankPawn* m_pPlayerTankPawn;

	ATankPawn* m_pAITankPawn;

};
