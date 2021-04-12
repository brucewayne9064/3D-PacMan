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

	void SetVulnerable();//���ܹ���
	void SetInVulnerable();//�����ܹ���

	void SetMove(bool MoveIt);//�����ƶ�
	void Killed();//���˱�ɱ���ص���ʼ�ص�
	void ReArm();//�ٶ���س�ֵ
	UFUNCTION()
	void OnCollection(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);//��ײ���


private:
	class UMaterialInterface* DefaultMaterial;//Ĭ�ϲ���
	class UMaterialInterface* VulnerableMaterial;//���ǿ��ԳԵ��˵Ĳ���
	FTimerHandle TimeVulnerable;//��ʱ��
	bool bIsVulnerable;
public:
	bool bIsDead;
};
