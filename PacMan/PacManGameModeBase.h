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
	Emenu,//��Ϸ������״̬
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
//������������Ŀ����Ϊ����ߺ�����ִ��Ч��
FORCEINLINE EGameState APacManGameModeBase::GetCurrentState() const {
	return currentState;
};