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

void AMonster::AddMoveVector(const FVector& _DirDelta)
{
	MoveVector += _DirDelta * MoveAcc;
}

void AMonster::AddUpDownMoveVector(const FVector& _DirDelta)
{
	MoveVector += _DirDelta * UpDownMoveAcc;
}

void AMonster::MoveUpdate(float _DeltaTime, bool _IsGravity, bool _IsGroundUp, bool _IsGroundDown)
{
	GroundTypeCheck();

	if (IsWallCheck() == true)
	{
		MoveVector = FVector::Zero;
	}

	if (State != EMonsterState::Absorb && MoveVector.Size2D() >= MoveMaxSpeed)
	{
		MoveVector = MoveVector.Normalize2DReturn() * MoveMaxSpeed;
	}

	if (_IsGravity == true)
	{
		GravityVector += GravityAcc * _DeltaTime;

		FVector Pos = { GetActorLocation().iX(), GetActorLocation().iY() };
		FVector PosL = { Pos.iX() - 25 , Pos.iY() };
		FVector PosR = { Pos.iX() + 25 , Pos.iY() };

		if (
			GroundType == EGroundType::SlopeUp ||
			GroundType == EGroundType::SlopeDown ||
			GroundType == EGroundType::ScarpUp ||
			GroundType == EGroundType::ScarpDown
			)
		{
			if (IsGroundCheck(Pos) == true)
			{
				GravityVector = FVector::Zero;
			}
		}
		else if (GroundType == EGroundType::Flat)
		{
			if (IsGroundCheck(PosL) == true || IsGroundCheck(PosR) == true)
			{
				GravityVector = FVector::Zero;
			}
		}

		if (GravityVector.Size2D() >= GravityMaxSpeed)
		{
			GravityVector = GravityVector.Normalize2DReturn() * GravityMaxSpeed;
		}
	}

	LastMoveVector = FVector::Zero;
	LastMoveVector = LastMoveVector + MoveVector;
	LastMoveVector = LastMoveVector + JumpVector;
	LastMoveVector = LastMoveVector + GravityVector;

	AddActorLocation(LastMoveVector * _DeltaTime);

	if (_IsGroundUp == true)
	{
		while (true)
		{
			FVector LeftPos = { GetActorLocation().iX() - 1, GetActorLocation().iY() - 3 };
			FVector RightPos = { GetActorLocation().iX() + 1, GetActorLocation().iY() - 3 };

			if (IsGroundCheck(LeftPos) || IsGroundCheck(RightPos))
			{
				AddActorLocation(FVector::Up);
			}
			else
			{
				break;
			}
		}
	}

	if (_IsGroundDown == true)
	{
		while (true)
		{
			FVector LeftPos = { GetActorLocation().iX() - 1, GetActorLocation().iY() + 2 };
			FVector RightPos = { GetActorLocation().iX() + 1, GetActorLocation().iY() + 2 };

			if (IsGroundCheck(LeftPos) == false && IsGroundCheck(RightPos) == false)
			{
				AddActorLocation(FVector::Down);
			}
			else
			{
				break;
			}
		}
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
	MoveVector = FVector::Zero;
	JumpVector = FVector::Zero;
	GravityVector = FVector::Zero;
}

void AMonster::Move(float _DeltaTime)
{

}

void AMonster::Attack(float _DeltaTime)
{
	
}

void AMonster::Absorb(float _DeltaTime)
{
	APlayer* Player = APlayer::GetMainPlayer();

	FVector PlayerPos = Player->GetActorLocation();
	FVector MonsterPos = GetActorLocation();

	FVector MonsterDir = PlayerPos - MonsterPos;
	FVector MonsterDirNormal = MonsterDir.Normalize2DReturn();

	MoveVector += MonsterDirNormal * _DeltaTime * 2000.0f;
	
	MoveUpdate(_DeltaTime, false, false, false);
}

void AMonster::DirCheck()
{
	EActorDir Dir = DirState;

	if (IsWallCheck() == true)
	{
		if (DirState == EActorDir::Left)
		{
			Dir = EActorDir::Right;
		}
		else if (DirState == EActorDir::Right)
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
}

void AMonster::UpDownDirCheck()
{

}

void AMonster::GroundTypeCheck()
{
	FVector Pos = { GetActorLocation().iX(), GetActorLocation().iY() + 5 };
	FVector PosL = { Pos.iX() - 25 , Pos.iY() };
	FVector PosR = { Pos.iX() + 25 , Pos.iY() };

	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(Pos.iX(), Pos.iY(), Color8Bit::MagentaA);
	Color8Bit ColorL = UContentsHelper::ColMapImage->GetColor(PosL.iX(), PosL.iY(), Color8Bit::MagentaA);
	Color8Bit ColorR = UContentsHelper::ColMapImage->GetColor(PosR.iX(), PosR.iY(), Color8Bit::MagentaA);

	if (Color == Color8Bit(255, 0, 255, 0))
	{
		GroundType = EGroundType::Flat;
	}
	else if (Color == Color8Bit(0, 255, 255, 0))
	{
		if (DirState == EActorDir::Left)
		{
			if (ColorL == Color8Bit(0, 0, 0, 0) || ColorR == Color8Bit(0, 255, 255, 0))
			{
				GroundType = EGroundType::SlopeDown;
			}
			else if (ColorL == Color8Bit(0, 255, 255, 0) || ColorR == Color8Bit(0, 0, 0, 0))
			{
				GroundType = EGroundType::SlopeUp;
			}
		}
		else if (DirState == EActorDir::Right)
		{
			if (ColorL == Color8Bit(0, 255, 255, 0) || ColorR == Color8Bit(0, 0, 0, 0))
			{
				GroundType = EGroundType::SlopeDown;
			}
			else if (ColorL == Color8Bit(0, 0, 0, 0) || ColorR == Color8Bit(0, 255, 255, 0))
			{
				GroundType = EGroundType::SlopeUp;
			}
		}
	}
	else if (Color == Color8Bit(255, 255, 0, 0))
	{
		if (DirState == EActorDir::Left)
		{
			if (ColorL == Color8Bit(0, 0, 0, 0) || ColorR == Color8Bit(255, 255, 0, 0))
			{
				GroundType = EGroundType::ScarpDown;
			}
			else if (ColorL == Color8Bit(255, 255, 0, 0) || ColorR == Color8Bit(0, 0, 0, 0))
			{
				GroundType = EGroundType::ScarpUp;
			}
		}
		else if (DirState == EActorDir::Right)
		{
			if (ColorL == Color8Bit(255, 255, 0, 0) || ColorR == Color8Bit(0, 0, 0, 0))
			{
				GroundType = EGroundType::ScarpDown;
			}
			else if (ColorL == Color8Bit(0, 0, 0, 0) || ColorR == Color8Bit(255, 255, 0, 0))
			{
				GroundType = EGroundType::ScarpUp;
			}
		}
	}
	else
	{
		GroundType = EGroundType::None;
	}
}

bool AMonster::IsGroundCheck(FVector _Pos)
{
	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(_Pos.iX(), _Pos.iY(), Color8Bit::WhiteA);
	if (
		Color == Color8Bit(255, 0, 255, 0) ||
		Color == Color8Bit(0, 255, 255, 0) ||
		Color == Color8Bit(255, 255, 0, 0)
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool AMonster::IsWallCheck()
{
	FVector CheckPosTop = { GetActorLocation().X, GetActorLocation().Y - 50 };
	FVector CheckPosCenter = { GetActorLocation().X, GetActorLocation().Y - 26 };
	FVector CheckPosBottom = { GetActorLocation().X, GetActorLocation().Y - 2 };

	switch (DirState)
	{
	case EActorDir::Left:
		CheckPosTop.X -= 25;
		CheckPosCenter.X -= 25;
		CheckPosBottom.X -= 25;
		break;
	case EActorDir::Right:
		CheckPosTop.X += 25;
		CheckPosCenter.X += 25;
		CheckPosBottom.X += 25;
		break;
	default:
		break;
	}

	Color8Bit ColorTop = UContentsHelper::ColMapImage->GetColor(CheckPosTop.iX(), CheckPosTop.iY(), Color8Bit::WhiteA);
	Color8Bit ColorCenter = UContentsHelper::ColMapImage->GetColor(CheckPosCenter.iX(), CheckPosCenter.iY(), Color8Bit::WhiteA);
	Color8Bit ColorBottom = UContentsHelper::ColMapImage->GetColor(CheckPosBottom.iX(), CheckPosBottom.iY(), Color8Bit::WhiteA);
	if (
		ColorTop == Color8Bit(255, 0, 255, 0) &&
		ColorCenter == Color8Bit(255, 0, 255, 0) &&
		ColorBottom == Color8Bit(255, 0, 255, 0)
		)
	{
		return true;
	}

	return false;
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

EAbiltyType AMonster::GetAbility() const
{
	return Ability;
}

void AMonster::SetAbility(EAbiltyType _Ability)
{
	Ability = _Ability;
}

void AMonster::SetMoveTimer(float _MoveTimer)
{
	MoveTimer = _MoveTimer;
}

void AMonster::SetMoveMaxSpeed(float _MoveMaxSpeed)
{
	MoveMaxSpeed = _MoveMaxSpeed;
}