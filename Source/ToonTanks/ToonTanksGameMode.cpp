// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    HandleGameStart();
}

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
    if (ATank* Tank = Cast<ATank>(DeadActor))
    {
        Tank->HandleDestruction();

        if (PlayerController)
        {
            PlayerController->SetPlayerEnabledState(false);
        }

        GameOver(false);
    }
    else if (ATower* Tower = Cast<ATower>(DeadActor))
    {
        Tower->HandleDestruction();
        TargetTowers--;

        if (TargetTowers == 0)
        {
            GameOver(true);
        }
    }
}

void AToonTanksGameMode::HandleGameStart()
{
    TargetTowers = GetTargetTowerCount();
    PlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();

    if(PlayerController)
    {
        PlayerController->SetPlayerEnabledState(false);

        FTimerHandle PlayerEnableTimerHandle;
        
        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
            PlayerController, 
            &AToonTanksPlayerController::SetPlayerEnabledState,
            true
        );

        GetWorldTimerManager().SetTimer(
            PlayerEnableTimerHandle, 
            PlayerEnableTimerDelegate, 
            StartDelay, 
            false
        );
    }
}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
    return Towers.Num();
}