// Fill out your copyright notice in the Description page of Project Settings.


#include "PcManCharacter.h"
#include"Kismet/GameplayStatics.h"
#include"Collectable.h"
#include"C:\Program Files\Epic Games\UE_4.25\Engine\Source\Runtime\Engine\Classes\Components\CapsuleComponent.h"
#include"Runtime/Engine/Public/EngineUtils.h"

// Sets default values
APcManCharacter::APcManCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APcManCharacter::BeginPlay()
{
	Super::BeginPlay();
	Lives = 3;
	StartPoint = GetActorLocation();//获得初始位置
	UE_LOG(LogTemp, Warning, TEXT("start point: %s"), *StartPoint.ToString());
	GameMode =Cast<APacManGameModeBase>(UGameplayStatics::GetGameMode(this));//获得当前状态
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APcManCharacter::OnCollection);//绑定碰撞

	for (TActorIterator<ACollectable> CollectableItr(GetWorld()); CollectableItr; ++CollectableItr) {
		CollectablesToEat++;//遍历豆子
	}
	UE_LOG(LogTemp, Warning, TEXT("total collectables are %d"), CollectablesToEat);
}

// Called every frame
void APcManCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APcManCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveX",this,&APcManCharacter::MoveXAxis);//轴映射绑定
	PlayerInputComponent->BindAxis("MoveY", this, &APcManCharacter::MoveYAxis);//轴映射绑定

	PlayerInputComponent->BindAction("NewGame",IE_Pressed, this, &APcManCharacter::NewGame);
	PlayerInputComponent->BindAction("ReStart", IE_Pressed, this, &APcManCharacter::ReStart);
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &APcManCharacter::Pause);
}

void APcManCharacter::MoveXAxis(float AxisValue)
{
	if (GameMode->GetCurrentState() == EGameState::Eplaying)
	{
		CurrentVelocity.X = AxisValue;
		AddMovementInput(CurrentVelocity);//把value传给该函数进行移动
	}

}

void APcManCharacter::MoveYAxis(float AxisValue)
{
	if (GameMode->GetCurrentState() == EGameState::Eplaying)
	{
		CurrentVelocity.Y = AxisValue;
		AddMovementInput(CurrentVelocity);
	}
}

void APcManCharacter::ReStart()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand(TEXT("ReStartLevel"));
}

void APcManCharacter::NewGame()
{
	if (GameMode->GetCurrentState() == EGameState::Emenu) {
		GameMode->SetCurrentState(EGameState::Eplaying);
	}
}

void APcManCharacter::Pause()
{
	if (GameMode->GetCurrentState() == EGameState::Eplaying) {
		GameMode->SetCurrentState(EGameState::Epause);
	}
	else if (GameMode->GetCurrentState() == EGameState::Epause) {
		GameMode->SetCurrentState(EGameState::Eplaying);
	}
}

void APcManCharacter::Killed()
{
	if (--Lives == 0)
	{
		GameMode->SetCurrentState(EGameState::EgameOver);
	}
	else {
		SetActorLocation(StartPoint);
	}
}

void APcManCharacter::OnCollection(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GameMode->GetCurrentState() == EGameState::Eplaying)//碰撞函数，碰到销毁
	{
		if (OtherActor->IsA(ACollectable::StaticClass())) {
			ACollectable* collectable = Cast<ACollectable>(OtherActor);
			if (collectable->bIsSuperCollectable) {//判断是不是红球，是的话设置敌人为易受攻击
				GameMode->SetEnemyVulnerable();
			}
			OtherActor->Destroy();
			if (--CollectablesToEat == 0) {
				GameMode->SetCurrentState(EGameState::Ewin);
			}
			UE_LOG(LogTemp, Warning, TEXT("remain collectables are %d"), CollectablesToEat);
		}
	}
}

