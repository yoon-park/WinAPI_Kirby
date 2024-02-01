#include "Player.h"

#include <EngineBase\EngineTime.h>
#include <EnginePlatform\EngineInput.h>
#include <EngineCore\EngineCore.h>
#include "Fire.h"

APlayer::APlayer()
{

}

APlayer::~APlayer()
{

}

void APlayer::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(0);
	Renderer->SetImage("Kirby.bmp");
	Renderer->SetImageCuttingTransform({ {0,0}, {16, 16} });
	Renderer->SetTransform({ {0,0}, {50, 50} });

	Renderer->CreateAnimation("Idle", "Kirby.bmp", 0, 5, 0.3f, true);
	Renderer->CreateAnimation("ThunderAttack", "Kirby.bmp", 6, 11, 0.3f, true);
	Renderer->ChangeAnimation("Idle");
}

void APlayer::Tick(float _DeltaTime)
{
	if (EngineInput::IsPress('A') == true)
	{
		AddActorLocation(FVector::Left * 500.0f * _DeltaTime);
	}

	if (EngineInput::IsPress('D') == true)
	{
		AddActorLocation(FVector::Right * 500.0f * _DeltaTime);
	}

	if (EngineInput::IsPress('W') == true)
	{
		AddActorLocation(FVector::Up * 500.0f * _DeltaTime);
	}

	if (EngineInput::IsPress('S') == true)
	{
		AddActorLocation(FVector::Down * 500.0f * _DeltaTime);
	}

	if (EngineInput::IsPress('Q') == true)
	{
		AFire* NewFire = GetWorld()->SpawnActor<AFire>();
		NewFire->SetActorLocation(GetActorLocation());
		NewFire->SetDir(FVector::Right);
	}

	if (EngineInput::IsPress('E') == true)
	{
		Renderer->ChangeAnimation("ThunderAttack");
	}
}