#include "Ability.h"

#include "Monster.h"

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