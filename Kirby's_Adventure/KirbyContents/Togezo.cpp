#include "Togezo.h"

ATogezo::ATogezo()
{

}

ATogezo::~ATogezo()
{

}

void ATogezo::BeginPlay()
{
	AMonster::BeginPlay();

	{
		Renderer = CreateImageRenderer(KirbyRenderOrder::Monster);
		Renderer->SetImage("PowerEnemy1_Left.png");
		Renderer->SetTransform({ {0,0}, {256, 256} });

		Renderer->CreateAnimation("Run_Left", "PowerEnemy1_Left.png", 29, 30, 0.1f, true);
		Renderer->CreateAnimation("Run_Right", "PowerEnemy1_Right.png", 29, 30, 0.1f, true);
		Renderer->CreateAnimation("Jump_Left", "PowerEnemy1_Left.png", 31, 33, 0.1f, true);
		Renderer->CreateAnimation("Jump_Right", "PowerEnemy1_Right.png", 31, 33, 0.1f, true);
		Renderer->CreateAnimation("Attack_Left", "PowerEnemy1_Left.png", 31, 33, 0.03f, true);
		Renderer->CreateAnimation("Attack_Right", "PowerEnemy1_Right.png", 31, 33, 0.03f, true);
	}
	{
		BodyCollision = CreateCollision(KirbyCollisionOrder::Monster);
		BodyCollision->SetColType(ECollisionType::Rect);
		BodyCollision->SetTransform({ {0, -25}, {50, 50} });
	}

	SetAbility(EAbiltyType::Needle);
	SetAttackTimer(2.5f);

	StateChange(EMonsterState::Move);
}

void ATogezo::Tick(float _DeltaTime)
{
	AMonster::Tick(_DeltaTime);
}

void ATogezo::MoveStart()
{
	AMonster::MoveStart();

	Renderer->ChangeAnimation(GetAnimationName("Run"));

	SetAnimationTimer(3.0f);
	SetMoveMaxSpeed(100.0f);
	MoveVector = FVector::Zero;
}

void ATogezo::JumpStart()
{
	AMonster::JumpStart();

	Renderer->ChangeAnimation(GetAnimationName("Jump"));
	DirCheck();

	MoveVector = FVector::Zero;
	JumpVector = JumpPower;
}

void ATogezo::BreakfallStart()
{
	AMonster::BreakfallStart();

	DirCheck();
	SetAnimationCount(2);
}

void ATogezo::AttackStart()
{
	AMonster::AttackStart();

	Renderer->ChangeAnimation(GetAnimationName("Attack"));
	DirCheck();

	SetAttackTimer(3.0f);
	SetAnimationTimer(0.3f);
	SetMoveMaxSpeed(700.0f);
}

void ATogezo::Move(float _DeltaTime)
{
	if (AbsorbCheck() == true)
	{
		StateChange(EMonsterState::Absorb);
		return;
	}

	if (AnimationTimer <= 0.0f)
	{
		StateChange(EMonsterState::Jump);
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

	AnimationTimer -= _DeltaTime;
	MoveUpdate(_DeltaTime, true, true, true);
}

void ATogezo::Jump(float _DeltaTime)
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

	MoveUpdate(_DeltaTime, true, false, false);
}

void ATogezo::Breakfall(float _DeltaTime)
{
	if (AbsorbCheck() == true)
	{
		StateChange(EMonsterState::Absorb);
		return;
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
		if (AnimationCount <= 0)
		{
			JumpVector = FVector::Zero;
			GravityVector = FVector::Zero;

			StateChange(EMonsterState::Attack);
			return;
		}
		AnimationCount -= 1;
	}
	else
	{
		MoveUpdate(_DeltaTime, true, false, false);
	}
}

void ATogezo::Attack(float _DeltaTime)
{
	if (AbsorbCheck() == true)
	{
		StateChange(EMonsterState::Absorb);
		return;
	}

	if (AttackTimer <= 0.0f)
	{
		SetAttackTimer(2.0f);

		StateChange(EMonsterState::Move);
		return;
	}

	EActorDir Dir = DirState;
	FVector LeftGround = { GetActorLocation().X - 5, GetActorLocation().Y + 2 };
	FVector RightGround = { GetActorLocation().X + 5, GetActorLocation().Y + 2 };

	if (
		DirState == EActorDir::Left && IsGroundCheck(LeftGround) == true || 
		DirState == EActorDir::Right && IsGroundCheck(RightGround) == true
		)
	{
		IsStop = true;
	}

	DirCheck();

	if (IsStop == true)
	{
		MoveVector = FVector::Zero;

		if(AnimationTimer <= 0.0f)
		{
			IsStop = false;
			SetAnimationTimer(0.3f);
		}
		else
		{
			AnimationTimer -= _DeltaTime;
		}
	}
	else
	{
		if (DirState == EActorDir::Left)
		{
			AddMoveVector(FVector::Left * _DeltaTime);
		}
		else if (DirState == EActorDir::Right)
		{
			AddMoveVector(FVector::Right * _DeltaTime);
		}
	}

	AttackTimer -= _DeltaTime;
	MoveUpdate(_DeltaTime, true, true, true);
}

void ATogezo::DirCheck()
{
	EActorDir Dir = DirState;
	FVector LeftGround = { GetActorLocation().X - 5, GetActorLocation().Y + 2 };
	FVector RightGround = { GetActorLocation().X + 5, GetActorLocation().Y + 2 };

	if (DirState == EActorDir::Left)
	{
		if (IsGroundCheck(LeftGround) == true)
		{
			Dir = EActorDir::Right;
		}
	}
	else if (DirState == EActorDir::Right)
	{
		if (IsGroundCheck(RightGround) == true)
		{
			Dir = EActorDir::Left;
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

void ATogezo::SetAnimationTimer(float _AnimationTimer)
{
	AnimationTimer = _AnimationTimer;
}

void ATogezo::SetAnimationCount(int _AnimationCount)
{
	AnimationCount = _AnimationCount;
}