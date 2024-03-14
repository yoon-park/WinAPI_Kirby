#include "Effect.h"

#include "Player.h"
#include "Monster.h"

AEffect::AEffect()
{

}

AEffect::~AEffect()
{

}

void AEffect::BeginPlay()
{
	AActor::BeginPlay();
}

void AEffect::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

void AEffect::DirCheck()
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

std::string AEffect::GetAnimationName(std::string _Name)
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

void AEffect::SetDirState(EActorDir _DirState)
{
	DirState = _DirState;

	std::string Name = GetAnimationName(CurAnimationName);
	Renderer->ChangeAnimation(Name, true, Renderer->GetCurAnimationFrame(), Renderer->GetCurAnimationTime());
}