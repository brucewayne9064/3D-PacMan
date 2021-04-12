// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include"Enemy.h"
#include"../PacManGameModeBase.h"
#include "AIEenmy.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_API AAIEenmy : public AAIController
{
	GENERATED_BODY()

public:
	void OnPossess(class APawn* InPawn) override;//¿‡À∆begin play
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	void SearchNewPoint();

	void GoHome();
	void ReArm();
	void StopMove();


private:
	class AEnemy* Bot;
	FVector HomeLocation;
	FTimerHandle DeadTime;
	APacManGameModeBase* GameMode;
};
