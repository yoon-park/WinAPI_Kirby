#include "HotHead.h"

#include <EngineBase/EngineRandom.h>
#include "Player.h"
#include "Fire.h"

AHotHead::AHotHead()
{

}

AHotHead::~AHotHead()
{

}

void AHotHead::BeginPlay()
{
	AMonster::BeginPlay();

	{
		Renderer = CreateImageRenderer(KirbyRenderOrder::Monster);
		Renderer->SetImage("PowerEnemy1_Left.png");
		Renderer->SetTransform({ {0,0}, {256, 256} });

		Renderer->CreateAnimation("Idle_Left", "PowerEnemy1_Left.png", 22, 22, 1.5f, false);
		Renderer->CreateAnimation("Idle_Right", "PowerEnemy1_Right.png", 22, 22, 1.5f, false);
		Renderer->CreateAnimation("Run_Left", "PowerEnemy1_Left.png", 22, 23, 0.1f, true);
		Renderer->CreateAnimation("Run_Right", "PowerEnemy1_Right.png", 22, 23, 0.1f, true);
		Renderer->CreateAnimation("Attack_Prepare_Left", "PowerEnemy1_Left.png", 24, 25, 0.03f, true);
		Renderer->CreateAnimation("Attack_Prepare_Right", "PowerEnemy1_Right.png", 24, 25, 0.03f, true);
		Renderer->CreateAnimation("Attack_Left", "PowerEnemy1_Left.png", 26, 27, 0.03f, true);
		Renderer->CreateAnimation("Attack_Right", "PowerEnemy1_Right.png", 26, 27, 0.03f, true);
	}
	{
		BodyCollision = CreateCollision(KirbyCollisionOrder::Monster);
		BodyCollision->SetColType(ECollisionType::Rect);
		BodyCollision->SetTransform({ {0, -25}, {50, 50} });

		DetectCollision = CreateCollision(KirbyCollisionOrder::Detect);
		DetectCollision->SetColType(ECollisionType::Rect);
		DetectCollision->SetTransform({ {0, -25}, {300, 150} });
	}

	SetAbility(EAbiltyType::Fire);
	SetAnimationTimer(0.1f);
	SetAttackTimer(2.5f);

	StateChange(EMonsterState::Idle);
}

void AHotHead::Tick(float _DeltaTime)
{
	AMonster::Tick(_DeltaTime);
}

void AHotHead::IdleStart()
{
	AMonster::IdleStart();

	Renderer->ChangeAnimation(GetAnimationName("Idle"));
}

void AHotHead::MoveStart()
{
	AMonster::MoveStart();

	Renderer->ChangeAnimation(GetAnimationName("Run"));
	DirCheck();
}

void AHotHead::AttackStart()
{
	AMonster::AttackStart();

	Renderer->ChangeAnimation(GetAnimationName("Attack_Prepare"));
	DirCheck();

	SetAnimationTimer(0.1f);
	MoveVector = FVector::Zero;
}

void AHotHead::Idle(float _DeltaTime)
{
	AMonster::Idle(_DeltaTime);

	if (Renderer->IsCurAnimationEnd())
	{
		StateChange(EMonsterState::Move);
		return;
	}

	MoveUpdate(_DeltaTime, true, true, true);
}

void AHotHead::Move(float _DeltaTime)
{
	AMonster::Move(_DeltaTime);

	if (DetectCheck() == true)
	{
		StateChange(EMonsterState::Attack);
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

	MoveUpdate(_DeltaTime, true, true, true);
}

void AHotHead::Attack(float _DeltaTime)
{
	AMonster::Attack(_DeltaTime);

	if (AbsorbCheck() == true)
	{
		SetAttackTimer(2.5f);
		SetCreateAbilityTimer(2.5f);

		StateChange(EMonsterState::Absorb);
		return;
	}

	if (AnimationTimer <= 0.0f)
	{
		Renderer->ChangeAnimation(GetAnimationName("Attack"));
	}
	else
	{
		AnimationTimer -= _DeltaTime;
		return;
	}

	if (AttackTimer <= 0.0f)
	{
		SetAttackTimer(2.5f);
		SetCreateAbilityTimer(2.5f);

		StateChange(EMonsterState::Idle);
		return;
	}
	AttackTimer -= _DeltaTime;

	{
		if ((CreateAbilityTimer - AttackTimer) >= 0.03f)
		{
			CreateAbilityTimer = AttackTimer;
			CreateAbility = true;
		}

		if (CreateAbility == true)
		{
			float AddPosX = UEngineRandom::MainRandom.RandomFloat(30.0f, 120.0f);
			if (DirState == EActorDir::Left)
			{
				AddPosX = -AddPosX;
			}
			float AddPosY = UEngineRandom::MainRandom.RandomFloat(-20.0f, 15.0f);

			FVector AbilityPos = { GetActorLocation().X + AddPosX, GetActorLocation().Y + AddPosY };

			AFire* Fire = GetWorld()->SpawnActor<AFire>();
			Fire->SetOwner(this);
			Fire->SetActorType(EActorType::Ability);
			Fire->SetActorLocation(AbilityPos);
			Fire->SetDirState(GetDirState());

			CreateAbility = false;
		}
	}

	MoveUpdate(_DeltaTime, true, true, true);
}

void AHotHead::DirCheck()
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

void AHotHead::SetAnimationTimer(float _AnimationTimer)
{
	AnimationTimer = _AnimationTimer;
}