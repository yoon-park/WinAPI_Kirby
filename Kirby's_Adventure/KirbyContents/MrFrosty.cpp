#include "MrFrosty.h"

#include "TheEnd.h"

AMrFrosty::AMrFrosty()
{

}

AMrFrosty::~AMrFrosty()
{

}

void AMrFrosty::BeginPlay()
{
	AMonster::BeginPlay();

	{
		Renderer = CreateImageRenderer(KirbyRenderOrder::Monster);
		Renderer->SetImage("MidBossEnemy_Left.png");
		Renderer->SetTransform({ {0,0}, {256, 256} });

		Renderer->CreateAnimation("Idle_Left", "MidBossEnemy_Left.png", 23, 23, 1.5f, true);
		Renderer->CreateAnimation("Idle_Right", "MidBossEnemy_Right.png", 23, 23, 1.5f, true);
		Renderer->CreateAnimation("Run_Left", "MidBossEnemy_Left.png", 30, 31, 0.1f, true);
		Renderer->CreateAnimation("Run_Right", "MidBossEnemy_Right.png", 30, 31, 0.1f, true);
		Renderer->CreateAnimation("Attack_Prepare_Left", "MidBossEnemy_Left.png", 24, 26, 0.1f, true);
		Renderer->CreateAnimation("Attack_Prepare_Right", "MidBossEnemy_Right.png", 24, 26, 0.1f, true);
		Renderer->CreateAnimation("Attack_Left", "MidBossEnemy_Left.png", 27, 29, 0.1f, true);
		Renderer->CreateAnimation("Attack_Right", "MidBossEnemy_Right.png", 27, 29, 0.1f, true);
		Renderer->CreateAnimation("Dead_Left", "MidBossEnemy_Left.png", 32, 32, 10.0f, true);
		Renderer->CreateAnimation("Dead_Right", "MidBossEnemy_Right.png", 32, 32, 10.0f, true);
	}
	{
		BodyCollision = CreateCollision(KirbyCollisionOrder::BossMonster);
		BodyCollision->SetColType(ECollisionType::Rect);
		BodyCollision->SetTransform({ {0, -25}, {50, 50} });
	}

	SetAbility(EAbiltyType::Freeze);

	StateChange(EMonsterState::Idle);
}

void AMrFrosty::Tick(float _DeltaTime)
{
	AMonster::Tick(_DeltaTime);
}

void AMrFrosty::IdleStart()
{
	AMonster::IdleStart();

	Renderer->ChangeAnimation(GetAnimationName("Idle"));
	DirCheck();
	MoveVector = FVector::Zero;
}

void AMrFrosty::MoveStart()
{
	AMonster::MoveStart();

	Renderer->ChangeAnimation(GetAnimationName("Run"));

	SetAnimationTimer(5.0f);
	SetMoveMaxSpeed(700.0f);
	MoveVector = FVector::Zero;
}

void AMrFrosty::AttackStart()
{
	AMonster::AttackStart();

	Renderer->ChangeAnimation(GetAnimationName("Attack_Prepare"));
	DirCheck();

	SetAttackTimer(2.0f);
	SetAnimationTimer(0.3f);
	SetMoveMaxSpeed(1000.0f);
}

void AMrFrosty::DeadStart()
{
	AMonster::DeadStart();

	Renderer->ChangeAnimation(GetAnimationName("Dead"));

	MoveVector = FVector::Zero;

	ATheEnd* TheEnd = GetWorld()->SpawnActor<ATheEnd>();
	TheEnd->SetName("Kirby");
	TheEnd->SetActorType(EActorType::Item);
	TheEnd->SetActorLocation({ 200, 400 });
}

void AMrFrosty::Idle(float _DeltaTime)
{
	if (HealthCount <= 0)
	{
		StateChange(EMonsterState::Dead);
		return;
	}

	if (Renderer->IsCurAnimationEnd())
	{
		StateChange(EMonsterState::Attack);
		return;
	}

	MoveUpdate(_DeltaTime, true, true, true);
}

void AMrFrosty::Move(float _DeltaTime)
{
	if (HealthCount <= 0)
	{
		StateChange(EMonsterState::Dead);
		return;
	}

	if (IsWallCheck() == true)
	{
		MoveVector = FVector::Zero;
		DirCheck();
	}

	if (AnimationTimer <= 0.0f)
	{
		StateChange(EMonsterState::Idle);
		return;
	}

	if (DirState == EActorDir::Left)
	{
		AddMoveVector(FVector::Left * _DeltaTime);
	}
	else if (DirState == EActorDir::Right)
	{
		AddMoveVector(FVector::Right * _DeltaTime);
	}

	AnimationTimer -= _DeltaTime;
	MoveUpdate(_DeltaTime, true, true, true);
}

void AMrFrosty::Attack(float _DeltaTime)
{
	if (HealthCount <= 0)
	{
		StateChange(EMonsterState::Dead);
		return;
	}

	if (AttackTimer <= 0.0f)
	{
		SetAttackTimer(2.0f);

		StateChange(EMonsterState::Move);
		return;
	}

	DirCheck();

	AttackTimer -= _DeltaTime;
	MoveUpdate(_DeltaTime, true, true, true);
}

void AMrFrosty::Dead(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		Destroy();
		return;
	}

	MoveUpdate(_DeltaTime, true, true, true);
}

void AMrFrosty::DirCheck()
{
	AMonster::DirCheck();
}

void AMrFrosty::SetAnimationTimer(float _AnimationTimer)
{
	AnimationTimer = _AnimationTimer;
}

void AMrFrosty::SetAnimationCount(int _AnimationCount)
{
	AnimationCount = _AnimationCount;
}