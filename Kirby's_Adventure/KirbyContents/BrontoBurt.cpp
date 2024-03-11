#include "BrontoBurt.h"

#include "Player.h"

ABrontoBurt::ABrontoBurt()
{

}

ABrontoBurt::~ABrontoBurt()
{

}

void ABrontoBurt::BeginPlay()
{
	AMonster::BeginPlay();

	{
		Renderer = CreateImageRenderer(KirbyRenderOrder::Monster);
		Renderer->SetImage("NormalEnemy_Left.png");
		Renderer->SetTransform({ {0,0}, {256, 256} });

		Renderer->CreateAnimation("Fly_Left", "NormalEnemy_Left.png", 29, 30, 0.15f, true);
		Renderer->CreateAnimation("Fly_Right", "NormalEnemy_Right.png", 29, 30, 0.15f, true);
	}
	{
		BodyCollision = CreateCollision(KirbyCollisionOrder::Monster);
		BodyCollision->SetColType(ECollisionType::Rect);
		BodyCollision->SetTransform({ {0, -25}, {50, 50} });
	}

	SetMoveTimer(1.3f);
	SetMoveMaxSpeed(150.0f);

	StateChange(EMonsterState::Move);
}

void ABrontoBurt::Tick(float _DeltaTime)
{
	AMonster::Tick(_DeltaTime);
}

void ABrontoBurt::UpDownDirCheck()
{
	AMonster::UpDownDirCheck();

	if (MoveTimer <= 0.0f)
	{
		if (UpDownDirState == EActorDir::Up)
		{
			UpDownDirState = EActorDir::Down;
		}
		else if (UpDownDirState == EActorDir::Down)
		{
			UpDownDirState = EActorDir::Up;
		}

		SetMoveTimer(1.5f);
	}
}

void ABrontoBurt::MoveStart()
{
	AMonster::MoveStart();

	SetMoveTimer(1.5f);
	Renderer->ChangeAnimation(GetAnimationName("Fly"));
}

void ABrontoBurt::Move(float _DeltaTime)
{
	AMonster::Move(_DeltaTime);

	if (AbsorbCheck() == true)
	{
		StateChange(EMonsterState::Absorb);
		return;
	}

	UpDownDirCheck();

	if (UpDownDirState == EActorDir::Up)
	{
		AddUpDownMoveVector(FVector::Up * _DeltaTime);
	}
	else if (UpDownDirState == EActorDir::Down)
	{
		AddUpDownMoveVector(FVector::Down * _DeltaTime);
	}

	AddMoveVector(FVector::Left * _DeltaTime);
	MoveTimer -= _DeltaTime;

	MoveUpdate(_DeltaTime, false, false, false);
}