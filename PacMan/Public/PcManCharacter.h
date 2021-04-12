// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include"../PacManGameModeBase.h"
#include"Collectable.h"
#include "PcManCharacter.generated.h"

UCLASS()
class PACMAN_API APcManCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APcManCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;//°ó¶¨°´¼ü

	void MoveXAxis(float AxisValue);
	void MoveYAxis(float AxisValue);

	void ReStart();
	void NewGame();
	void Pause();

	void Killed();

	UFUNCTION()
	void OnCollection(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);//Åö×²¼ì²â
	
	int CollectablesToEat;
	int Lives;

private:
	FVector CurrentVelocity;//¿ØÖÆÒÆ¶¯
	FVector StartPoint;
	APacManGameModeBase* GameMode;



};
