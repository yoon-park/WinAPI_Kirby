#include "PoppyBrosJr.h"

#include "Player.h"

APoppyBrosJr::APoppyBrosJr()
{

}

APoppyBrosJr::~APoppyBrosJr()
{

}

void APoppyBrosJr::BeginPlay()
{
	AMonster::BeginPlay();

	{
		Renderer = CreateImageRenderer(KirbyRenderOrder::Monster);
		Renderer->SetImage("NormalEnemy_Left.png");
		Renderer->SetTransform({ {0,0}, {256, 256} });

		Renderer->CreateAnimation("Jump_Left", "NormalEnemy_Left.png", 17, 17, 0.1f, false);
		Renderer->CreateAnimation("Jump_Right", "NormalEnemy_Right.png", 17, 17, 0.1f, false);
		Renderer->CreateAnimation("Breakfall_Left", "NormalEnemy_Left.png", 16, 16, 0.1f, false);
		Renderer->CreateAnimation("Breakfall_Right", "NormalEnemy_Right.png", 16, 16, 0.1f, false);
	}
	{
		BodyCollision = CreateCollision(KirbyCollisionOrder::Monster);
		BodyCollision->SetColType(ECollisionType::Rect);
		BodyCollision->SetTransform({ {0, -25}, {50, 50} });

		DetectCollision = CreateCollision(KirbyCollisionOrder::Detect);
		DetectCollision->SetColType(ECollisionType::Rect);
		DetectCollision->SetTransform({ {0, -75}, {300, 150} });
	}

	StateChange(EMonsterState::Jump);
}

void APoppyBrosJr::Tick(float _DeltaTime)
{
	AMonster::Tick(_DeltaTime);
}

void APoppyBrosJr::JumpStart()
{
	AMonster::JumpStart();

	Renderer->ChangeAnimation(GetAnimationName("Jump"));
	DirCheck();

	JumpVector = JumpPower;
}

void APoppyBrosJr::BreakfallStart()
{
	AMonster::BreakfallStart();

	Renderer->ChangeAnimation(GetAnimationName("Breakfall"));
	DirCheck();
}

void APoppyBrosJr::Jump(float _DeltaTime)
{
	AMonster::Jump(_DeltaTime);

	if (JumpVector.Y + GravityVector.Y > 0.0f)
	{
		StateChange(EMonsterState::Breakfall);
		return;
	}

	if (AbsorbCheck() == true)
	{
		StateChange(EMonsterState::Absorb);
		return;
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

	if (IsWallCheck() == true)
	{
		MoveVector = FVector::Zero;
	}

	MoveUpdate(_DeltaTime, true, false, false);
}

void APoppyBrosJr::Breakfall(float _DeltaTime)
{
	if (AbsorbCheck() == true)
	{
		StateChange(EMonsterState::Absorb);
		return;
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

	if (IsWallCheck() == true)
	{
		MoveVector = FVector::Zero;
	}

	GroundTypeCheck();

	FVector Ground = { GetActorLocation().iX(), GetActorLocation().iY() };

	if (
		GroundType == EGroundType::SlopeUp ||
		GroundType == EGroundType::SlopeDown ||
		GroundType == EGroundType::ScarpUp ||
		GroundType == EGroundType::ScarpDown
		)
	{
		Ground = { GetActorLocation().iX() , GetActorLocation().iY() + 5 };
	}

	if (IsGroundCheck(Ground) == true)
	{
		JumpVector = FVector::Zero;
		GravityVector = FVector::Zero;

		StateChange(EMonsterState::Jump);
		return;
	}
	else
	{
		MoveUpdate(_DeltaTime, true, false, false);
	}
}

void APoppyBrosJr::DirCheck()
{
	EActorDir Dir = DirState;

	std::vector<UCollision*> Result;
	if (DetectCollision->CollisionCheck(KirbyCollisionOrder::Player, Result) == true)
	{
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		APlayer* Player = dynamic_cast<APlayer*>(Ptr);

		if (Player == nullptr)
		{
			MsgBoxAssert("Player가 존재하지 않습니다.");
		}

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
	}

	if (Dir != DirState)
	{
		DirState = Dir;
		std::string Name = GetAnimationName(CurAnimationName);
		Renderer->ChangeAnimation(Name, true, Renderer->GetCurAnimationFrame(), Renderer->GetCurAnimationTime());
	}

	AMonster::DirCheck();
}