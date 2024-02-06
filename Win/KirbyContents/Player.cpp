#include "Player.h"

#include <EngineBase\EngineTime.h>
#include <EnginePlatform\EngineInput.h>
#include <EngineCore\EngineCore.h>
#include "ContentsHelper.h"
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

	Renderer = CreateImageRenderer(KirbyRenderOrder::Player);
	Renderer->SetImage("Kirby_right.png");
	Renderer->SetTransform({ {0,0}, {128, 128} });

	Renderer->CreateAnimation("Idle", "Kirby_right.png", 0, 1, 0.3f, true);
	Renderer->CreateAnimation("Move", "Kirby_right.png", 2, 5, 0.1f, true);

	Renderer->ChangeAnimation("Idle");
}

void APlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (UContentsHelper::ColMapImage == nullptr)
	{
		MsgBoxAssert("맵 이미지가 존재하지 않아 충돌할 수 없습니다.");
	}
	
	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY());

	if (Color != Color8Bit(255, 0, 255, 0))
	{
		AddActorLocation(FVector::Down * _DeltaTime * Gravity);
	}

	if (EngineInput::IsPress('A') == true)
	{
		Renderer->ChangeAnimation("Move");
		AddActorLocation(FVector::Left * 500.0f * _DeltaTime);
	}

	if (EngineInput::IsPress('D') == true)
	{
		Renderer->ChangeAnimation("Move");
		AddActorLocation(FVector::Right * 500.0f * _DeltaTime);
	}

	if (EngineInput::IsPress('W') == true)
	{
		Renderer->ChangeAnimation("Idle");
	}

	if (EngineInput::IsPress('S') == true)
	{
		Renderer->ChangeAnimation("Idle");
	}

	if (EngineInput::IsPress('Q') == true)
	{
		AFire* NewFire = GetWorld()->SpawnActor<AFire>();
		NewFire->SetActorLocation(GetActorLocation());
		NewFire->SetDir(FVector::Right);
	}
}