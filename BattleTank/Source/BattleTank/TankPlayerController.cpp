// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankPawn.h"

ATankPlayerController::ATankPlayerController()
{
	m_pTankPawn = nullptr;
	
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	m_pTankPawn = Cast<ATankPawn>(GetPawn());

	if(m_pTankPawn != nullptr)
		UE_LOG(LogTemp, Warning, TEXT("PlayerController %s has controller in Begin Play"), *(m_pTankPawn->GetName()));
}

ATankPawn* ATankPlayerController::GetControlledTank()
{
	if(m_pTankPawn != nullptr)
		return m_pTankPawn;
	else
		return Cast<ATankPawn>(GetPawn());
}