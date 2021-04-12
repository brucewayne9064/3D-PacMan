// Fill out your copyright notice in the Description page of Project Settings.


#include "AIEenmy.h"
#include"NavigationSystem.h"
#include"Kismet/GameplayStatics.h"
#include"C:\Program Files\Epic Games\UE_4.25\Engine\Source\Runtime\Engine\Public\TimerManager.h"

void AAIEenmy::OnPossess(class APawn* InPawn) {
	Super::OnPossess(InPawn);
	Bot = Cast<AEnemy>(InPawn);
	HomeLocation = Bot->GetActorLocation();
	GameMode = Cast<APacManGameModeBase>(UGameplayStatics::GetGameMode(this));
	SearchNewPoint();
}

void AAIEenmy::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if (!Bot->bIsDead && GameMode->GetCurrentState()!= EGameState::Epause) {
		SearchNewPoint();
	}
}

void AAIEenmy::SearchNewPoint()
{
	UNavigationSystemV1* NavMesh = UNavigationSystemV1::GetCurrent(this);
	if (NavMesh) {//判断导航网格是否存在
		const float SearchRadius = 10000.0f;//搜索半径
		FNavLocation RandomPt;//保存位置信息

		const bool bFound = NavMesh->GetRandomReachablePointInRadius(Bot->GetActorLocation(),SearchRadius,RandomPt);
		if (bFound) {//如果位置存在，移动到该位置
			MoveToLocation(RandomPt);
		}
	}
}

void AAIEenmy::GoHome()
{
	MoveToLocation(HomeLocation);
	GetWorldTimerManager().SetTimer(DeadTime, this, &AAIEenmy::ReArm, 5.0f, false);
}

void AAIEenmy::ReArm()
{
	GetWorldTimerManager().ClearTimer(DeadTime);
	Bot->ReArm();
}

void AAIEenmy::StopMove()
{
	MoveToLocation(Bot->GetActorLocation());
}
