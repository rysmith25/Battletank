// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPawn.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"

ATankAIController::ATankAIController()
{

}

void ATankAIController::BeginPlay()
{
	m_pAITankPawn = Cast<ATankPawn>(GetPawn());

	if (GetWorld())
		m_pPlayerTankPawn = Cast<ATankPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (m_pPlayerTankPawn)
		UE_LOG(LogTemp, Warning, TEXT("AI found PlayerTank %s in the world"), *(m_pPlayerTankPawn->GetName()));
}

ATankPawn * ATankAIController::GetAITankPawn()
{
	if (m_pAITankPawn)
		return m_pAITankPawn;
	else
		return Cast<ATankPawn>(GetPawn());	
}

ATankPawn * ATankAIController::GetPlayerTankPawn()
{
	if (m_pPlayerTankPawn)
		return m_pPlayerTankPawn;
	else
		return Cast<ATankPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
}