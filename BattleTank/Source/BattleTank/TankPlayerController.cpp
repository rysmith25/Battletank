// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankPawn.h"
#include "Engine/World.h"

ATankPlayerController::ATankPlayerController()
{
	m_pTankPawn = nullptr;

	PrimaryActorTick.bCanEverTick = true;

	m_CrossHairXLocation = 0.5f;
	m_CrossHairYLocation = 0.3333f;
	m_LineTraceRange = 1000000.0f;
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
		UE_LOG(LogTemp, Warning, TEXT("Look Direction is %s"), *HitLocation.ToString());
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& endLocation) const
{
	bool bHitSomething = false;

	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;	
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * m_CrossHairXLocation, ViewportSizeY * m_CrossHairYLocation);

	// Get Look Direction, De-project
	FVector CameraWorldDirection;
	if (GetLookDirection(ScreenLocation, CameraWorldDirection))
	{
		GetLookVectorHitLocation(CameraWorldDirection, endLocation);
		bHitSomething = true;
	}
	
	return bHitSomething;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const
{
	// "De-projected" the screen position of the crosshair to a world direction
	FVector CameraWorldLocation;
	
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection))
		return true;
	else
		return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector & HitLocation) const
{
	// Line trace along look direction
	bool bHitVector = false;	
	FHitResult hitResult;
	FVector startLocation = PlayerCameraManager->GetCameraLocation();
	FVector endLocation = startLocation + (LookDirection * m_LineTraceRange);
	ECollisionChannel colChannel = ECollisionChannel::ECC_Visibility;
	FCollisionQueryParams colParams = FCollisionQueryParams::DefaultQueryParam;
	FCollisionResponseParams colResponse = FCollisionResponseParams::DefaultResponseParam;
	
	if(GetWorld()->LineTraceSingleByChannel(hitResult, startLocation, endLocation, colChannel, colParams, colResponse))
	{
		bHitVector = true;
		HitLocation = hitResult.Location;
	}

	return bHitVector;
}
