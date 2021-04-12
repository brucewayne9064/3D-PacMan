// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "UObject/ConstructorHelpers.h"
#include"Components/CapsuleComponent.h"
#include"C:\Program Files\Epic Games\UE_4.25\Engine\Source\Runtime\Engine\Public\TimerManager.h"
#include"C:\Program Files\Epic Games\UE_4.25\Engine\Source\Runtime\Engine\Classes\GameFramework\CharacterMovementComponent.h"
#include"C:\users\bruce\documents\unreal projects\pacman\Source\PacMan\Public\PcManCharacter.h"
#include"C:\users\bruce\documents\unreal projects\pacman\Source\PacMan\Public\AIEenmy.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EnemyBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderObj(TEXT("'/Game/StarterContent/Shapes/Shape_Cylinder'"));

	if (CylinderObj.Succeeded()) {
		EnemyBody->SetStaticMesh(CylinderObj.Object);
	}

	EnemyBody->SetRelativeScale3D(FVector(0.7f, 0.7f, 1.0f));
	EnemyBody->SetRelativeLocation(FVector(0, 0, -50));
	EnemyBody->AttachTo(RootComponent);

	GetCapsuleComponent()->SetCapsuleRadius(40.0f);
	GetCapsuleComponent()->SetCapsuleHalfHeight(50.0f);


	static ConstructorHelpers::FObjectFinder<UMaterial> VulnerableMat(TEXT("'/Game/Materials/M_Enemy_Vulnerable'"));
	if (VulnerableMat.Succeeded())
	{
		VulnerableMaterial = Cast<UMaterialInterface>(VulnerableMat.Object);
	}
	SetActorEnableCollision(true);
	AIControllerClass = AAIEenmy::StaticClass();
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	DefaultMaterial = EnemyBody->GetMaterial(0);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnCollection);//绑定碰撞
	//SetVulnerable();
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::SetVulnerable()
{
	GetWorldTimerManager().SetTimer(TimeVulnerable, this, &AEnemy::SetInVulnerable, 10.0f, false);//计时,吃到豆子时间间隔就要增加，
	if (bIsVulnerable)                                                                           //但是如果敌人已经是灰色就不改变颜色
	{
		return;
	}
	bIsVulnerable = true;
	EnemyBody->SetMaterial(0, VulnerableMaterial);//设置成易受攻击的材质
	GetCharacterMovement()->MaxWalkSpeed = 50.0f;//速度小，主角容易吃到
	
}

void AEnemy::SetInVulnerable()
{
	GetWorldTimerManager().ClearTimer(TimeVulnerable);
	bIsVulnerable = false;
	EnemyBody->SetMaterial(0, DefaultMaterial);//材质变回初始材质
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;//速度大，主角容易被追到
}

void AEnemy::SetMove(bool MoveIt)
{
	AAIEenmy* AI = Cast<AAIEenmy>(GetController());
	if (MoveIt) {
		AI->SearchNewPoint();
	}
	else {
		AI->StopMove();
	}
}

void AEnemy::Killed()
{
	if (bIsDead)
	{
		return;
	}
	bIsDead = true;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	AAIEenmy* AI = Cast<AAIEenmy>(GetController());
	AI->GoHome();
}

void AEnemy::ReArm()
{
	bIsDead = false;
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
	if (bIsVulnerable) {
		SetInVulnerable();
	}
	SetMove(true);
}

void AEnemy::OnCollection(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APcManCharacter::StaticClass())) {
		if (bIsVulnerable) {
			Killed();//被主角吃
		}
		else {
			APcManCharacter* PacMan = Cast<APcManCharacter>(OtherActor);
			PacMan->Killed();//吃主角
		}
	}
}

