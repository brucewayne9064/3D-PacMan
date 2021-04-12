// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include"Components/SphereComponent.h"
#include"Components/StaticMeshComponent.h"
#include "Collectable.generated.h"

UCLASS()
class PACMAN_API ACollectable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = Collectable)
	UStaticMeshComponent* CollectableMesh;//网格组件，用来显示形状

	UPROPERTY(EditDefaultsOnly, Category = Collectable)
	USphereComponent* BaseCollisionComponent;//碰撞组件，检测两个物体碰撞

	UPROPERTY(EditAnywhere, Category = Collectable)
	bool bIsSuperCollectable;//是否为超级敌人
};
