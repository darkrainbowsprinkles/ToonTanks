// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
    if (ATank* Tank = Cast<ATank>(DeadActor))
    {
        Tank->HandleDestruction();

        APlayerController* PlayerController = Tank->GetPlayerController();

        if (PlayerController)
        {
            Tank->DisableInput(PlayerController);
            PlayerController->bShowMouseCursor = false;
        }
    }
    else if (ATower* Tower = Cast<ATower>(DeadActor))
    {
        Tower->HandleDestruction();
    }
}