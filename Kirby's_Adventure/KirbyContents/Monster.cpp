#include "Monster.h"

#include "ContentsHelper.h"
#include "Player.h"

AMonster::AMonster()
{

}

AMonster::~AMonster()
{

}

void AMonster::BeginPlay()
{
	AActor::BeginPlay();

	StateChange(EMonsterState::Move);
}

void AMonster::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void AMonster::StateChange(EMonsterState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EMonsterState::Move:
			MoveStart();
			break;
		case EMonsterState::Attack:
			AttackStart();
			break;
		case EMonsterState::Absorb:
			AbsorbStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void AMonster::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EMonsterState::Move:
		Move(_DeltaTime);
		break;
	case EMonsterState::Attack:
		Attack(_DeltaTime);
		break;
	case EMonsterState::Absorb:
		Absorb(_DeltaTime);
		break;
	default:
		break;
	}
}

void AMonster::MoveStart()
{

}

void AMonster::AttackStart()
{

}

void AMonster::AbsorbStart()
{

}

void AMonster::Move(float _DeltaTime)
{
	if (AbsorbCheck() == true)
	{
		StateChange(EMonsterState::Absorb);
	}
}

void AMonster::Attack(float _DeltaTime)
{
	if (AbsorbCheck() == true)
	{
		StateChange(EMonsterState::Absorb);
	}
}

void AMonster::Absorb(float _DeltaTime)
{
	APlayer* Player = APlayer::GetMainPlayer();

	FVector PlayerPos = Player->GetActorLocation();
	FVector MonsterPos = GetActorLocation();

	FVector MonsterDir = PlayerPos - MonsterPos;
	FVector MonsterDirNormal = MonsterDir.Normalize2DReturn();

	AddActorLocation(MonsterDirNormal * _DeltaTime * 200.0f);
}

void AMonster::DirCheck()
{
	EActorDir Dir = DirState;

	/*if (UEngineInput::IsPress(VK_LEFT))
	{
		Dir = EActorDir::Left;
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		Dir = EActorDir::Right;
	}*/

	if (Dir != DirState)
	{
		DirState = Dir;
		std::string Name = GetAnimationName(CurAnimationName);
		Renderer->ChangeAnimation(Name, true, Renderer->GetCurAnimationFrame(), Renderer->GetCurAnimationTime());
	}
}

bool AMonster::AbsorbCheck()
{
	std::vector<UCollision*> Result;
	if (BodyCollision->CollisionCheck(KirbyCollisionOrder::PlayerAbsorb, Result) == true)
	{
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		APlayer* Player = dynamic_cast<APlayer*>(Ptr);

		if (Player == nullptr)
		{
			MsgBoxAssert("Player가 존재하지 않습니다.");
		}

		return true;
	}

	return false;
}

std::string AMonster::GetAnimationName(std::string _Name)
{
	std::string DirName = "";

	switch (DirState)
	{
	case EActorDir::Left:
		DirName = "_Left";
		break;
	case EActorDir::Right:
		DirName = "_Right";
		break;
	default:
		break;
	}

	CurAnimationName = _Name;

	return _Name + DirName;
}