// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ACollectable::ACollectable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SetActorEnableCollision(true);//开启碰撞，默认是关闭的
	CollectableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollectableMesh"));//创建网格组件
	BaseCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("BaseCollisionComponent"));//创建碰撞体，球形sphere
	CollectableMesh->AttachTo(BaseCollisionComponent);//把网格和碰撞体绑定

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Sphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));//找球体
	if (Sphere.Succeeded()) {
		CollectableMesh->SetStaticMesh(Sphere.Object);//如果找到球体指定给mesh
	}

	CollectableMesh->SetWorldScale3D(FVector(0.3, 0.3, 0.3));
	BaseCollisionComponent->SetSphereRadius(16);
}

// Called when the game starts or when spawned
void ACollectable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollectable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

