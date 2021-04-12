// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ACollectable::ACollectable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SetActorEnableCollision(true);//������ײ��Ĭ���ǹرյ�
	CollectableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollectableMesh"));//�����������
	BaseCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("BaseCollisionComponent"));//������ײ�壬����sphere
	CollectableMesh->AttachTo(BaseCollisionComponent);//���������ײ���

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Sphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));//������
	if (Sphere.Succeeded()) {
		CollectableMesh->SetStaticMesh(Sphere.Object);//����ҵ�����ָ����mesh
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

