// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankPawn.h"

ATankPlayerController::ATankPlayerController()
{
	m_pTankPawn = nullptr;

	m_pTankPawn = Cast<ATankPawn>(GetPawn());
}

ATankPawn* ATankPlayerController::GetControlledTank()
{
	if(m_pTankPawn != nullptr)
		return m_pTankPawn;
	else
		return Cast<ATankPawn>(GetPawn());
}