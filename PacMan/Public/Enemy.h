// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class PACMAN_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = Body)
	UStaticMeshComponent* EnemyBody;

	void SetVulnerable();//易受攻击
	void SetInVulnerable();//不易受攻击

	void SetMove(bool MoveIt);//敌人移动
	void Killed();//敌人被杀，回到初始地点
	void ReArm();//速度设回初值
	UFUNCTION()
	void OnCollection(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);//碰撞检测


private:
	class UMaterialInterface* DefaultMaterial;//默认材质
	class UMaterialInterface* VulnerableMaterial;//主角可以吃敌人的材质
	FTimerHandle TimeVulnerable;//定时器
	bool bIsVulnerable;
public:
	bool bIsDead;
};
