// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::BeginPlay() 
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (TankInFireRange())
    {
        RotateTurret(Tank->GetActorLocation());
    }
}

void ATower::HandleDestruction()
{
    Super::HandleDestruction();
    
    Destroy();
}

void ATower::CheckFireCondition()
{
    if (TankInFireRange())
    {
        Fire();
    }
}

bool ATower::TankInFireRange()
{
    if (Tank)
    {
        float DistanceToTank = FVector::Distance(GetActorLocation(), Tank->GetActorLocation());
        return DistanceToTank <= FireRange;
    }

    return false;
}