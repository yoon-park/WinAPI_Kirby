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
	SetActorLocation({ 100, 100 });
	Renderer->SetImageCuttingTransform({ {0,0}, {16, 16} });
	Renderer->SetTransform({ {0,0}, {50, 50} });
}

void APlayer::Tick(float _DeltaTime)
{
	if (true == EngineInput::IsPress('A'))
	{
		AddActorLocation(FVector::Left * 500.0f * _DeltaTime);
	}

	if (true == EngineInput::IsPress('D'))
	{
		AddActorLocation(FVector::Right * 500.0f * _DeltaTime);
	}

	if (true == EngineInput::IsPress('W'))
	{
		AddActorLocation(FVector::Up * 500.0f * _DeltaTime);
	}

	if (true == EngineInput::IsPress('S'))
	{
		AddActorLocation(FVector::Down * 500.0f * _DeltaTime);
	}

	if (true == EngineInput::IsPress('Q'))
	{
		AFire* NewFire = GetWorld()->SpawnActor<AFire>();
		NewFire->SetActorLocation(GetActorLocation());
		NewFire->SetDir(FVector::Right);
	}
}