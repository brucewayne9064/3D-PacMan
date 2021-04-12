// Copyright Epic Games, Inc. All Rights Reserved.


#include "PacManGameModeBase.h"
#include"Runtime/Engine/Public/EngineUtils.h"

void APacManGameModeBase::SetCurrentState(EGameState value)
{
	currentState = value;
	switch (value)
	{
	case EGameState::Eplaying:
		for (auto Iter(Enemys.CreateIterator()); Iter; Iter++)
		{
			(*Iter)->SetMove(true);
		}
		break;
	case EGameState::Epause:
		for (auto Iter(Enemys.CreateIterator()); Iter; Iter++)
		{
			(*Iter)->SetMove(false);
		}
		break;
	case EGameState::Ewin:
		for (auto Iter(Enemys.CreateIterator()); Iter; Iter++)
		{
			(*Iter)->Destroy();
		}
		break;
	case EGameState::EgameOver:
		for (auto Iter(Enemys.CreateIterator()); Iter; Iter++)
		{
			(*Iter)->Destroy();
		}
		break;
	default:
		break;
	}
}

void APacManGameModeBase::SetEnemyVulnerable()
{
	for (auto Iter(Enemys.CreateIterator()); Iter; Iter++)
	{
		(*Iter)->SetVulnerable();
	}
}

void APacManGameModeBase::BeginPlay()
{
	SetCurrentState(EGameState::Emenu);

	for (TActorIterator<AEnemy> enemyIter(GetWorld()); enemyIter; ++enemyIter) {
		AEnemy* enemy = Cast<AEnemy>(*enemyIter);
		if (enemy) {
			Enemys.Add(enemy);//找到所有敌人
		}
	}
}
