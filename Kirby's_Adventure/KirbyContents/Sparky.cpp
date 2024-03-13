#include "Sparky.h"

#include <EngineBase/EngineRandom.h>
#include "Player.h"
#include "Spark.h"

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

		Renderer->CreateAnimation("Idle_Left", "PowerEnemy1_Left.png", 11, 11, 0.5f, false);
		Renderer->CreateAnimation("Idle_Right", "PowerEnemy1_Right.png", 11, 11, 0.5f, false);
		Renderer->CreateAnimation("Jump_Left", "PowerEnemy1_Left.png", 10, 10, 0.2f, false);
		Renderer->CreateAnimation("Jump_Right", "PowerEnemy1_Right.png", 10, 10, 0.2f, false);
		Renderer->CreateAnimation("Breakfall_Left", "PowerEnemy1_Left.png", 12, 12, 0.2f, false);
		Renderer->CreateAnimation("Breakfall_Right", "PowerEnemy1_Right.png", 12, 12, 0.2f, false);
		Renderer->CreateAnimation("Attack_Left", "PowerEnemy1_Left.png", 13, 14, 0.03f, true);
		Renderer->CreateAnimation("Attack_Right", "PowerEnemy1_Right.png", 13, 14, 0.03f, true);
	}
	{
		BodyCollision = CreateCollision(KirbyCollisionOrder::Monster);
		BodyCollision->SetColType(ECollisionType::Rect);
		BodyCollision->SetTransform({ {0, -25}, {50, 50} });
		
		DetectCollision = CreateCollision(KirbyCollisionOrder::Detect);
		DetectCollision->SetColType(ECollisionType::Rect);
		DetectCollision->SetTransform({ {0, -75}, {300, 150} });
	}

	SetAbility(EAbiltyType::Spark);
	SetJumpPower(FVector::Up * 700.0f);
	SetAttackTimer(2.0f);

	StateChange(EMonsterState::Idle);
}

void ASparky::Tick(float _DeltaTime)
{
	AMonster::Tick(_DeltaTime);
}

void ASparky::IdleStart()
{
	AMonster::IdleStart();

	Renderer->ChangeAnimation(GetAnimationName("Idle"));
	DirCheck();
}

void ASparky::JumpStart()
{
	AMonster::JumpStart();

	Renderer->ChangeAnimation(GetAnimationName("Jump"));
	DirCheck();

	JumpVector = JumpPower;
}

void ASparky::BreakfallStart()
{
	AMonster::BreakfallStart();

	Renderer->ChangeAnimation(GetAnimationName("Breakfall"));
	DirCheck();
}

void ASparky::FallStart()
{
	AMonster::BreakfallStart();

	Renderer->ChangeAnimation(GetAnimationName("Breakfall"));
	DirCheck();
}

void ASparky::AttackStart()
{
	AMonster::AttackStart();

	Renderer->ChangeAnimation(GetAnimationName("Attack"));
	DirCheck();

	AttackCollision = CreateCollision(KirbyCollisionOrder::MonsterAbilty);
	AttackCollision->SetColType(ECollisionType::Rect);
	AttackCollision->SetTransform({ {0, 0}, {130, 130} });

	MoveVector = FVector::Zero;
	JumpVector = FVector::Zero;
	GravityVector = FVector::Zero;
}

void ASparky::AbsorbStart()
{
	AMonster::AbsorbStart();
}

void ASparky::Idle(float _DeltaTime)
{
	AMonster::Idle(_DeltaTime);

	if (DetectCheck() == true)
	{
		if (Renderer->IsCurAnimationEnd())
		{
			StateChange(EMonsterState::Attack);
			return;
		}
	}

	if (AbsorbCheck() == true)
	{
		StateChange(EMonsterState::Absorb);
		return;
	}

	if (Renderer->IsCurAnimationEnd())
	{
		StateChange(EMonsterState::Jump);
		return;
	}

	if (MoveVector.Size2D() > 0.0f)
	{
		MoveVector -= MoveVector.Normalize2DReturn() * _DeltaTime * MoveAcc;
	}

	MoveUpdate(_DeltaTime, true, true, true);
}

void ASparky::Jump(float _DeltaTime)
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

	MoveUpdate(_DeltaTime, true, false, false);
}

void ASparky::Breakfall(float _DeltaTime)
{
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

		StateChange(EMonsterState::Idle);
		return;
	}
	else
	{
		MoveUpdate(_DeltaTime, true, false, false);
	}
}

void ASparky::Fall(float _DeltaTime)
{

}

void ASparky::Attack(float _DeltaTime)
{
	if (AbsorbCheck() == true)
	{
		AttackCollision->Destroy();
		SetAttackTimer(2.0f);
		SetCreateAbilityTimer(2.0f);

		StateChange(EMonsterState::Absorb);
		return;
	}

	if (AttackTimer <= 0.0f)
	{
		AttackCollision->Destroy();
		SetAttackTimer(2.0f);
		SetCreateAbilityTimer(2.0f);

		StateChange(EMonsterState::Idle);
		return;
	}
	AttackTimer -= _DeltaTime;

	if ((CreateAbilityTimer - AttackTimer) >= 0.03f)
	{
		CreateAbilityTimer = AttackTimer;
		CreateAbility = true;
	}
	
	if(CreateAbility == true)
	{
		float AddPosX = UEngineRandom::MainRandom.RandomFloat(-50.0f, 50.0f);
		float AddPosY = UEngineRandom::MainRandom.RandomFloat(-50.0f, 50.0f);
		FVector AbilityPos = { GetActorLocation().X + AddPosX, GetActorLocation().Y + AddPosY };

		ASpark* Spark = GetWorld()->SpawnActor<ASpark>();
		Spark->SetOwner(this);
		Spark->SetActorType(EActorType::Ability);
		Spark->SetActorLocation(AbilityPos);
		Spark->SetDirState(GetDirState());

		CreateAbility = false;
	}
	MoveUpdate(_DeltaTime, true, true, true);
}

void ASparky::Absorb(float _DeltaTime)
{
	if (AbsorbCheck() == false)
	{
		StateChange(EMonsterState::Idle);
		return;
	}

	AMonster::Absorb(_DeltaTime);
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

void ASparky::SetCreateAbilityTimer(float _CreateAbilityTimer)
{
	CreateAbilityTimer = _CreateAbilityTimer;
}