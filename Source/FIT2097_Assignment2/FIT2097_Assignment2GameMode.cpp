// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "FIT2097_Assignment2.h"
#include "FIT2097_Assignment2GameMode.h"
#include "FIT2097_Assignment2Character.h"

AFIT2097_Assignment2GameMode::AFIT2097_Assignment2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// base decay rate
	DecayRate = 0.02f;

	// base value for how frequent to drain power
	HealthDrainDelay = 0.25f;
}

void AFIT2097_Assignment2GameMode::BeginPlay()
{
	Super::BeginPlay();

	// access the world to get to players
	UWorld* World = GetWorld();
	check(World); // better than if functions for performance because world should be valid

}

float AFIT2097_Assignment2GameMode::GetDecayRate()
{
	return DecayRate;
}

void AFIT2097_Assignment2GameMode::DrainHealthOvertime()
{
	// access the world to get to players
	UWorld* World = GetWorld();
	check(World); // better than if functions for performance because world should be valid

	// AAssignment_2GameState* MyGameState = Cast<AAssignment_2GameState>(GameState);
	// check(MyGameState);

	// go through all the characters in the game and drain power from them
	for (FConstControllerIterator It = World->GetControllerIterator(); It; It++)
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(*It))
		{
			if (AFIT2097_Assignment2Character* Character = Cast<AFIT2097_Assignment2Character>(PlayerController->GetPawn()))
			{
				Character->UpdateHealth(-HealthDrainDelay*DecayRate*(Character->GetMaxHealth()));

				// if player's health is equal to or less than 0, kill the player
				if (Character->GetCurrentHealth() <= 0)
				{
					// player has died
					Character->OnPlayerDeath();

					// see if this is the last player to die, and end the game if it is
					/*
					DeadPlayerCount++;
					if (DeadPlayerCount >= GetNumPlayers())
					{
						HandleNewState(EPlayState::EGameOver);
					}
					*/
				}
			}
		}
	}
}