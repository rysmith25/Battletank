// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankPawn.h"
#include "Engine/World.h"

ATankPlayerController::ATankPlayerController()
{
	m_pTankPawn = nullptr;

	PrimaryActorTick.bCanEverTick = true;	
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	m_pTankPawn = Cast<ATankPawn>(GetPawn());
	
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimAtCrosshair();
}

ATankPawn* ATankPlayerController::GetControlledTank()
{
	if(m_pTankPawn != nullptr)
		return m_pTankPawn;
	else
		return Cast<ATankPawn>(GetPawn());
}

void ATankPlayerController::AimAtCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation = FVector(0);

	if(GetSightRayHitLocation(HitLocation))
		UE_LOG(LogTemp, Warning, TEXT("The hit location is %s"), *HitLocation.ToString());
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& endLocation) const
{
	bool bHitSomething = false;
	FHitResult hitResult;
	FVector startLocation;
	
	ECollisionChannel colChannel = ECollisionChannel::ECC_Visibility;
	FCollisionQueryParams colParams = FCollisionQueryParams::DefaultQueryParam;
	FCollisionResponseParams colResponse = FCollisionResponseParams::DefaultResponseParam;

	GetWorld()->LineTraceSingleByChannel(hitResult, startLocation, endLocation, colChannel, colParams, colResponse);

	if (hitResult.Actor != nullptr)
		bHitSomething = true;

	return bHitSomething;
}
