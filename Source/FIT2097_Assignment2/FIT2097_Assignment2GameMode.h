// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameModeBase.h"
#include "FIT2097_Assignment2GameMode.generated.h"

UCLASS(minimalapi)
class AFIT2097_Assignment2GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFIT2097_Assignment2GameMode();

	// start the health drain timer in here
	virtual void BeginPlay() override;

	// get current rate of decay
	UFUNCTION(BlueprintPure, Category = "Decay")
		float GetDecayRate();

protected:
	// how many times per second to update characters stats and check game rules
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Decay")
		float HealthDrainDelay;

	// access the timer for recurrring health draining
	FTimerHandle HealthDrainTimer;

	// the rate at which the character loses stats at percentage of character's stats per second
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Decay", meta = (BlueprintProtected = "true"))
		float DecayRate;

private:
	// drains power from characters and update gameplay
	void DrainHealthOvertime();
};



