// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include"Public/Enemy.h"
#include "PacManGameModeBase.generated.h"


/**
 * 
 */

enum class EGameState :short {
	Emenu,//游戏的五种状态
	Eplaying,
	Epause,
	Ewin,
	EgameOver

};

UCLASS()
class PACMAN_API APacManGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	/// <summary>
	virtual void BeginPlay() override;
	/// </summary>
	EGameState GetCurrentState() const;

	void SetCurrentState(EGameState value);

	void SetEnemyVulnerable();

private:
	EGameState currentState;
	TArray<class AEnemy*> Enemys;
};
//内联函数，其目的是为了提高函数的执行效率
FORCEINLINE EGameState APacManGameModeBase::GetCurrentState() const {
	return currentState;
};