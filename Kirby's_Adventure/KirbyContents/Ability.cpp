#include "Ability.h"

#include "Player.h"
#include "Monster.h"
#include "DisappearEffect.h"

AAbility::AAbility()
{

}

AAbility::~AAbility()
{

}

void AAbility::BeginPlay()
{
	AActor::BeginPlay();
}

void AAbility::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	AttackCheck();
}

void AAbility::DirCheck()
{
	EActorDir Dir = DirState;

	if (Owner->GetActorType() == EActorType::Player)
	{
		APlayer* Player = APlayer::GetMainPlayer();

		if (Player->GetDirState() == EActorDir::Left)
		{
			Dir = EActorDir::Left;
		}

		if (Player->GetDirState() == EActorDir::Right)
		{
			Dir = EActorDir::Right;
		}
	}
	else if (Owner->GetActorType() == EActorType::Monster)
	{
		AMonster* Monster = dynamic_cast<AMonster*>(Owner);

		if (Monster->GetDirState() == EActorDir::Left)
		{
			Dir = EActorDir::Left;
		}

		if (Monster->GetDirState() == EActorDir::Right)
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
}

bool AAbility::IsWallCheck()
{
	return false;
}

std::string AAbility::GetAnimationName(std::string _Name)
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

void AAbility::SetDirState(EActorDir _DirState)
{
	DirState = _DirState;

	std::string Name = GetAnimationName(CurAnimationName);
	Renderer->ChangeAnimation(Name, true, Renderer->GetCurAnimationFrame(), Renderer->GetCurAnimationTime());
}

void AAbility::AttackCheck()
{
	if (Owner->GetActorType() == EActorType::Player)
	{
		std::vector<UCollision*> Result;

		if (AttackCollision->CollisionCheck(KirbyCollisionOrder::Monster, Result) == true)
		{
			UCollision* Collision = Result[0];
			AActor* Ptr = Collision->GetOwner();
			AMonster* Monster = dynamic_cast<AMonster*>(Ptr);

			if (Monster == nullptr)
			{
				MsgBoxAssert("Monster가 존재하지 않습니다.");
			}

			ADisappearEffect* DisappearEffect = GetWorld()->SpawnActor<ADisappearEffect>();
			DisappearEffect->SetActorType(EActorType::Effect);
			DisappearEffect->SetActorLocation(GetActorLocation());

			Monster->Destroy();

			return;
		}

		if (AttackCollision->CollisionCheck(KirbyCollisionOrder::BossMonster, Result) == true)
		{
			UCollision* Collision = Result[0];
			AActor* Ptr = Collision->GetOwner();
			AMonster* Monster = dynamic_cast<AMonster*>(Ptr);

			if (Monster == nullptr)
			{
				MsgBoxAssert("Monster가 존재하지 않습니다.");
			}

			Monster->SubHealthCount();

			return;
		}
	}
}