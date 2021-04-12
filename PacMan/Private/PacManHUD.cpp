// Fill out your copyright notice in the Description page of Project Settings.


#include "PacManHUD.h"
#include"Kismet/GameplayStatics.h"
#include"c:\users\bruce\documents\unreal projects\pacman\Source\PacMan\PacManGameModeBase.h"
#include"C:\Program Files\Epic Games\UE_4.25\Engine\Source\Runtime\Engine\Classes\Engine\Canvas.h"
#include"c:\users\bruce\documents\unreal projects\pacman\Source\PacMan\Public\PcManCharacter.h"

void APacManHUD::DrawHUD()
{
	class APacManGameModeBase* GameMode = Cast<APacManGameModeBase>(UGameplayStatics::GetGameMode(this));//获得当前状态
	switch(GameMode->GetCurrentState())
	{
	case EGameState::Emenu:
		DrawText(TEXT("Welcome to PacMan!\n\nNEW GAME(N)\nPAUSE(P)"),FColor::White,(Canvas->SizeX/2.0f)-320.0f, (Canvas->SizeY / 2.0f)-150.0f,HUDFont);
		break;
	case EGameState::Eplaying:
	{
		APcManCharacter* PacMan = Cast<APcManCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
		if (PacMan) {
			FString LiveString = TEXT("Lives:") + FString::FromInt(PacMan->Lives);
			DrawText(LiveString, FColor::Green, 50.0f, 50.0f, HUDFont);
			FString CollectablesToEatString = TEXT("Beans To Eat:") + FString::FromInt(PacMan->CollectablesToEat);
			DrawText(CollectablesToEatString, FColor::Green, Canvas->SizeX -500.0f, 50.0f, HUDFont);
		}
	}
		break;
	case EGameState::Epause:
		DrawText(TEXT("P To Continue"), FColor::White, (Canvas->SizeX / 2.0f) - 210.0f, (Canvas->SizeY / 2.0f) - 150.0f, HUDFont);
		break;
	case EGameState::Ewin:
		DrawText(TEXT("You Win!\n\nR To Restart"), FColor::White, (Canvas->SizeX / 2.0f) - 175.0f, (Canvas->SizeY / 2.0f) - 150.0f, HUDFont);
		break;
	case EGameState::EgameOver:
		DrawText(TEXT("Game Over!\n\nR To Restart"), FColor::White, (Canvas->SizeX / 2.0f) - 175.0f, (Canvas->SizeY / 2.0f) - 150.0f, HUDFont);
		break;
	default:
		break;
	}
}
