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
	StartPoint = GetActorLocation();//��ó�ʼλ��
	UE_LOG(LogTemp, Warning, TEXT("start point: %s"), *StartPoint.ToString());
	GameMode =Cast<APacManGameModeBase>(UGameplayStatics::GetGameMode(this));//��õ�ǰ״̬
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APcManCharacter::OnCollection);//����ײ

	for (TActorIterator<ACollectable> CollectableItr(GetWorld()); CollectableItr; ++CollectableItr) {
		CollectablesToEat++;//��������
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
	PlayerInputComponent->BindAxis("MoveX",this,&APcManCharacter::MoveXAxis);//��ӳ���
	PlayerInputComponent->BindAxis("MoveY", this, &APcManCharacter::MoveYAxis);//��ӳ���

	PlayerInputComponent->BindAction("NewGame",IE_Pressed, this, &APcManCharacter::NewGame);
	PlayerInputComponent->BindAction("ReStart", IE_Pressed, this, &APcManCharacter::ReStart);
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &APcManCharacter::Pause);
}

void APcManCharacter::MoveXAxis(float AxisValue)
{
	if (GameMode->GetCurrentState() == EGameState::Eplaying)
	{
		CurrentVelocity.X = AxisValue;
		AddMovementInput(CurrentVelocity);//��value�����ú��������ƶ�
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
	if (GameMode->GetCurrentState() == EGameState::Eplaying)//��ײ��������������
	{
		if (OtherActor->IsA(ACollectable::StaticClass())) {
			ACollectable* collectable = Cast<ACollectable>(OtherActor);
			if (collectable->bIsSuperCollectable) {//�ж��ǲ��Ǻ����ǵĻ����õ���Ϊ���ܹ���
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

