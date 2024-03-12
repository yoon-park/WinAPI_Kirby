#include "Sparky.h"

#include "Player.h"

ASparky::ASparky()
{

}

ASparky::~ASparky()
{

}

void ASparky::BeginPlay()
{
	AMonster::BeginPlay();

	{
		Renderer = CreateImageRenderer(KirbyRenderOrder::Monster);
		Renderer->SetImage("PowerEnemy1_Left.png");
		Renderer->SetTransform({ {0,0}, {256, 256} });

		Renderer->CreateAnimation("Run_Left", "PowerEnemy1_Left.png", 10, 12, 0.2f, true);
		Renderer->CreateAnimation("Run_Right", "PowerEnemy1_Left.png", 10, 12, 0.2f, true);
	}
	{
		BodyCollision = CreateCollision(KirbyCollisionOrder::Monster);
		BodyCollision->SetColType(ECollisionType::Rect);
		BodyCollision->SetTransform({ {0, -25}, {50, 50} });
	}

	SetAbility(EAbiltyType::Spark);
	SetMoveMaxSpeed(100.0f);

	StateChange(EMonsterState::Move);
}

void ASparky::Tick(float _DeltaTime)
{
	AMonster::Tick(_DeltaTime);
}

void ASparky::MoveStart()
{
	AMonster::MoveStart();

	Renderer->ChangeAnimation(GetAnimationName("Run"));
	DirCheck();
}

void ASparky::Move(float _DeltaTime)
{
	AMonster::Move(_DeltaTime);

	if (AbsorbCheck() == true)
	{
		StateChange(EMonsterState::Absorb);
		return;
	}

	if (IsWallCheck() == true)
	{
		MoveVector = FVector::Zero;
	}

	DirCheck();

	if (DirState == EActorDir::Left)
	{
		AddMoveVector(FVector::Left * _DeltaTime);
	}
	else if (DirState == EActorDir::Right)
	{
		AddMoveVector(FVector::Right * _DeltaTime);
	}

	FVector Ground = { GetActorLocation().iX(), GetActorLocation().iY() + 5 };

	if (IsGroundCheck(Ground) == false)
	{
		MoveUpdate(_DeltaTime, true, false, false);
	}
	else
	{
		MoveUpdate(_DeltaTime, true, true, true);
	}
}

void ASparky::DirCheck()
{
	EActorDir Dir = DirState;

	APlayer* Player = APlayer::GetMainPlayer();

	FVector PlayerPos = Player->GetActorLocation();
	FVector MonsterPos = GetActorLocation();

	FVector MonsterDir = PlayerPos - MonsterPos;

	if (MonsterDir.X < 0)
	{
		Dir = EActorDir::Left;
	}
	else if (MonsterDir.X > 0)
	{
		Dir = EActorDir::Right;
	}

	if (Dir != DirState)
	{
		DirState = Dir;
		std::string Name = GetAnimationName(CurAnimationName);
		Renderer->ChangeAnimation(Name, true, Renderer->GetCurAnimationFrame(), Renderer->GetCurAnimationTime());
	}

	AMonster::DirCheck();
}