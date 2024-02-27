#include "Player.h"

#include <EngineBase\EngineTime.h>
#include <EnginePlatform\EngineInput.h>
#include <EngineCore\EngineCore.h>
#include "ContentsHelper.h"

APlayer* APlayer::MainPlayer = nullptr;

APlayer* APlayer::GetMainPlayer()
{
	return MainPlayer;
}

APlayer::APlayer()
{

}

APlayer::~APlayer()
{

}

void APlayer::BeginPlay()
{
	AActor::BeginPlay();

	MainPlayer = this;

	{
		Renderer = CreateImageRenderer(KirbyRenderOrder::Player);
		Renderer->SetImage("Kirby_Right.png");
		Renderer->SetTransform({ {0,0}, {256, 256} });

		Renderer->CreateAnimation("Idle_Right", "Kirby_Right.png", 0, 1, 0.5f, true);
		Renderer->CreateAnimation("Idle_SlopeUp_Right", "Kirby_Right.png", 10, 10, 0.1f, true);
		Renderer->CreateAnimation("Idle_SlopeDown_Right", "Kirby_Right.png", 11, 11, 0.1f, true);
		Renderer->CreateAnimation("Idle_ScarpUp_Right", "Kirby_Right.png", 14, 14, 0.1f, true);
		Renderer->CreateAnimation("Idle_ScarpDown_Right", "Kirby_Right.png", 15, 15, 0.1f, true);
		Renderer->CreateAnimation("Run_Right", "Kirby_Right.png", 2, 5, 0.1f, true);
		Renderer->CreateAnimation("Run_ScarpUp_Right", "Kirby_Right.png", 16, 19, 0.1f, true);
		Renderer->CreateAnimation("Run_ScarpDown_Right", "Kirby_Right.png", 20, 20, 0.1f, true);
		Renderer->CreateAnimation("Dash_Right", "Kirby_Right.png", 2, 5, 0.07f, true);
		Renderer->CreateAnimation("Dash_ScarpUp_Right", "Kirby_Right.png", 16, 19, 0.07f, true);
		Renderer->CreateAnimation("Dash_ScarpDown_Right", "Kirby_Right.png", 20, 20, 0.07f, true);
		Renderer->CreateAnimation("Break_Left", "Kirby_Right.png", 6, 6, 0.15f, false);
		Renderer->CreateAnimation("Jump_Right", "Kirby_Right.png", 23, 23, 0.1f, true);
		Renderer->CreateAnimation("Breakfall_Right", "Kirby_Right.png", 24, 27, 0.07f, false);
		Renderer->CreateAnimation("Fall_Right", "Kirby_Right.png", 27, 27, 0.1f, false);
		Renderer->CreateAnimation("Crashland_Right", "Kirby_Right.png", 28, 28, 0.1f, false);
		Renderer->CreateAnimation("Crouch_Right", "Kirby_Right.png", 8, 8, 0.07f, true);
		Renderer->CreateAnimation("Crouch_SlopeUp_Right", "Kirby_Right.png", 12, 12, 0.07f, true);
		Renderer->CreateAnimation("Crouch_SlopeDown_Right", "Kirby_Right.png", 13, 13, 0.07f, true);
		Renderer->CreateAnimation("Crouch_ScarpUp_Right", "Kirby_Right.png", 21, 21, 0.07f, true);
		Renderer->CreateAnimation("Crouch_ScarpDown_Right", "Kirby_Right.png", 22, 22, 0.07f, true);
		Renderer->CreateAnimation("Squeeze_Right", "Kirby_Right.png", 7, 7, 0.1f, false);
		Renderer->CreateAnimation("Absorb_Fly_Right", "Kirby_Right.png", 29, 32, 0.1f, false);
		Renderer->CreateAnimation("Fly_Right", "Kirby_Right.png", 33, 34, 0.5f, true);
		Renderer->CreateAnimation("Spit_Fly_Right", "Kirby_Right.png", 35, 38, 0.1f, false);

		Renderer->CreateAnimation("Idle_Left", "Kirby_Left.png", 0, 1, 0.5f, true);
		Renderer->CreateAnimation("Idle_SlopeUp_Left", "Kirby_Left.png", 10, 10, 0.1f, true);
		Renderer->CreateAnimation("Idle_SlopeDown_Left", "Kirby_Left.png", 11, 11, 0.1f, true);
		Renderer->CreateAnimation("Idle_ScarpUp_Left", "Kirby_Left.png", 14, 14, 0.1f, true);
		Renderer->CreateAnimation("Idle_ScarpDown_Left", "Kirby_Left.png", 15, 15, 0.1f, true);
		Renderer->CreateAnimation("Run_Left", "Kirby_Left.png", 2, 5, 0.1f, true);
		Renderer->CreateAnimation("Run_ScarpUp_Left", "Kirby_Left.png", 16, 19, 0.1f, true);
		Renderer->CreateAnimation("Run_ScarpDown_Left", "Kirby_Left.png", 20, 20, 0.1f, true);
		Renderer->CreateAnimation("Dash_Left", "Kirby_Left.png", 2, 5, 0.07f, true);
		Renderer->CreateAnimation("Dash_ScarpUp_Left", "Kirby_Left.png", 16, 19, 0.07f, true);
		Renderer->CreateAnimation("Dash_ScarpDown_Left", "Kirby_Left.png", 20, 20, 0.07f, true);
		Renderer->CreateAnimation("Break_Right", "Kirby_Left.png", 6, 6, 0.15f, false);
		Renderer->CreateAnimation("Jump_Left", "Kirby_Left.png", 23, 23, 0.1f, true);
		Renderer->CreateAnimation("Breakfall_Left", "Kirby_Left.png", 24, 27, 0.07f, false);
		Renderer->CreateAnimation("Fall_Left", "Kirby_Left.png", 27, 27, 0.1f, false);
		Renderer->CreateAnimation("Crashland_Left", "Kirby_Left.png", 28, 28, 0.1f, false);
		Renderer->CreateAnimation("Crouch_Left", "Kirby_Left.png", 8, 8, 0.07f, true);
		Renderer->CreateAnimation("Crouch_SlopeUp_Left", "Kirby_Left.png", 12, 12, 0.07f, true);
		Renderer->CreateAnimation("Crouch_SlopeDown_Left", "Kirby_Left.png", 13, 13, 0.07f, true);
		Renderer->CreateAnimation("Crouch_ScarpUp_Left", "Kirby_Left.png", 21, 21, 0.07f, true);
		Renderer->CreateAnimation("Crouch_ScarpDown_Left", "Kirby_Left.png", 22, 22, 0.07f, true);
		Renderer->CreateAnimation("Squeeze_Left", "Kirby_Left.png", 7, 7, 0.1f, false);
		Renderer->CreateAnimation("Absorb_Fly_Left", "Kirby_Left.png", 29, 32, 0.1f, false);
		Renderer->CreateAnimation("Fly_Left", "Kirby_Left.png", 33, 34, 0.5f, true);
		Renderer->CreateAnimation("Spit_Fly_Left", "Kirby_Left.png", 35, 38, 0.1f, false);
	}

	{
		BodyCollision = CreateCollision(KirbyCollisionOrder::Player);
		BodyCollision->SetColType(ECollisionType::Rect);
		BodyCollision->SetTransform({ {0, -32}, { 64, 64 } });
	}

	StateChange(EPlayState::Idle);
}

void APlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

std::string APlayer::GetAnimationName(std::string _Name)
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

void APlayer::DirCheck()
{
	EActorDir Dir = DirState;

	if (UEngineInput::IsPress(VK_LEFT))
	{
		Dir = EActorDir::Left;
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		Dir = EActorDir::Right;
	}

	if (Dir != DirState)
	{
		DirState = Dir;
		std::string Name = GetAnimationName(CurAnimationName);
		Renderer->ChangeAnimation(Name, true, Renderer->GetCurAnimationFrame(), Renderer->GetCurAnimationTime());
	}
}

void APlayer::GroundTypeCheck()
{
	FVector Pos = { GetActorLocation().iX(), GetActorLocation().iY() + 5};
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

bool APlayer::IsGroundCheck(FVector _Pos)
{
	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(_Pos.iX(), _Pos.iY(), Color8Bit::MagentaA);
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

bool APlayer::IsWallCheck()
{
	FVector CheckPos = GetActorLocation();

	switch (DirState)
	{
	case EActorDir::Left:
		CheckPos.X -= 26;
		break;
	case EActorDir::Right:
		CheckPos.X += 26;
		break;
	default:
		break;
	}
	CheckPos.Y -= 32;

	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(CheckPos.iX(), CheckPos.iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		return true;
	}

	return false;
}

bool APlayer::IsLeftWallCheck()
{
	FVector CheckPos = GetActorLocation();
	CheckPos.X -= 26;
	CheckPos.Y -= 32;

	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(CheckPos.iX(), CheckPos.iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		return true;
	}

	return false;
}

bool APlayer::IsRightWallCheck()
{
	FVector CheckPos = GetActorLocation();
	CheckPos.X += 26;
	CheckPos.Y -= 32;

	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(CheckPos.iX(), CheckPos.iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		return true;
	}

	return false;
}

void APlayer::DashOn()
{
	MoveMaxSpeed = 400.0f;
}

void APlayer::DashOff()
{
	MoveMaxSpeed = 300.0f;
}

void APlayer::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EPlayState::CameraFreeMove:
		CameraFreeMove(_DeltaTime);
		break;
	case EPlayState::FreeMove:
		FreeMove(_DeltaTime);
		break;
	case EPlayState::Idle:
		Idle(_DeltaTime);
		break;
	case EPlayState::Run:
		Run(_DeltaTime);
		break;
	case EPlayState::Dash:
		Dash(_DeltaTime);
		break;
	case EPlayState::Break:
		Break(_DeltaTime);
		break;
	case EPlayState::Jump:
		Jump(_DeltaTime);
		break;
	case EPlayState::Breakfall:
		Breakfall(_DeltaTime);
		break;
	case EPlayState::Fall:
		Fall(_DeltaTime);
		break;
	case EPlayState::Crouch:
		Crouch(_DeltaTime);
		break;
	case EPlayState::Squeeze:
		Squeeze(_DeltaTime);
		break;
	case EPlayState::Fly:
		Fly(_DeltaTime);
		break;
	case EPlayState::SpitFly:
		SpitFly(_DeltaTime);
		break;
	default:
		break;
	}
}

void APlayer::StateChange(EPlayState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EPlayState::Idle:
			IdleStart();
			break;
		case EPlayState::Run:
			RunStart();
			break;
		case EPlayState::Dash:
			DashStart();
			break;
		case EPlayState::Break:
			BreakStart();
			break;
		case EPlayState::Jump:
			JumpStart();
			break;
		case EPlayState::Breakfall:
			BreakfallStart();
			break;
		case EPlayState::Fall:
			FallStart();
			break;
		case EPlayState::Crouch:
			CrouchStart();
			break;
		case EPlayState::Squeeze:
			SqueezeStart();
			break;
		case EPlayState::Fly:
			FlyStart();
			break;
		case EPlayState::SpitFly:
			SpitFlyStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void APlayer::CameraFreeMove(float _DeltaTime)
{
	if (UEngineInput::IsDown('2'))
	{
		StateChange(EPlayState::Idle);
		return;
	}

	if (UEngineInput::IsPress(VK_LEFT))
	{
		GetWorld()->AddCameraPos(FVector::Left * _DeltaTime * 500.0f);
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		GetWorld()->AddCameraPos(FVector::Right * _DeltaTime * 500.0f);
	}

	if (UEngineInput::IsPress(VK_UP))
	{
		GetWorld()->AddCameraPos(FVector::Up * _DeltaTime * 500.0f);
	}

	if (UEngineInput::IsPress(VK_DOWN))
	{
		GetWorld()->AddCameraPos(FVector::Down * _DeltaTime * 500.0f);
	}
}

void APlayer::FreeMove(float _DeltaTime)
{
	DirCheck();
	FVector FreeMove = FVector::Zero;

	if (UEngineInput::IsDown('1'))
	{
		StateChange(EPlayState::Idle);
		return;
	}

	if (UEngineInput::IsPress(VK_LEFT))
	{
		FreeMove = FVector::Left * _DeltaTime * FreeMoveSpeed;
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		FreeMove = FVector::Right * _DeltaTime * FreeMoveSpeed;
	}

	if (UEngineInput::IsPress(VK_UP))
	{
		FreeMove = FVector::Up * _DeltaTime * FreeMoveSpeed;
	}

	if (UEngineInput::IsPress(VK_DOWN))
	{
		FreeMove = FVector::Down * _DeltaTime * FreeMoveSpeed;
	}

	AddActorLocation(FreeMove);
	GetWorld()->AddCameraPos(FreeMove);
}

void APlayer::Idle(float _DeltaTime)
{
	if (UEngineInput::IsDown('1'))
	{
		StateChange(EPlayState::FreeMove);
		return;
	}

	if (UEngineInput::IsDown('2'))
	{
		StateChange(EPlayState::CameraFreeMove);
		return;
	}

	if (IsWallCheck() == false)
	{
		if (UEngineInput::IsPress(VK_LEFT) || UEngineInput::IsPress(VK_RIGHT))
		{
 			StateChange(EPlayState::Run);
			return;
		}
	}
	else if (IsRightWallCheck() == true)
	{
		if (UEngineInput::IsPress(VK_LEFT))
		{
			StateChange(EPlayState::Run);
			return;
		}
	}
	else if (IsLeftWallCheck() == true)
	{
		if (UEngineInput::IsPress(VK_RIGHT))
		{
			StateChange(EPlayState::Run);
			return;
		}
	}

	if (UEngineInput::IsDown('X'))
	{
		StateChange(EPlayState::Jump);
		return;
	}

	if (UEngineInput::IsPress(VK_DOWN))
	{
		StateChange(EPlayState::Crouch);
		return;
	}

	if (UEngineInput::IsDown(VK_UP))
	{
		StateChange(EPlayState::Fly);
		return;
	}

	MoveUpdate(_DeltaTime, true, true, true);
}

void APlayer::Run(float _DeltaTime)
{
	EActorDir PrevDir = DirState;
	DirCheck();
	EGroundType PrevGround = GroundType;
	GroundTypeCheck();
	
	if (GroundType != PrevGround)
	{
		if (GroundType == EGroundType::Flat)
		{
			MoveMaxSpeed = 300.0f;
			Renderer->ChangeAnimation(GetAnimationName("Run"));
		}
		else if (GroundType == EGroundType::SlopeUp)
		{
			MoveMaxSpeed = 200.0f;
			Renderer->ChangeAnimation(GetAnimationName("Run"));
		}
		else if (GroundType == EGroundType::SlopeDown)
		{
			MoveMaxSpeed = 350.0f;
			Renderer->ChangeAnimation(GetAnimationName("Run"));
		}
		else if (GroundType == EGroundType::ScarpUp)
		{
			MoveMaxSpeed = 100.0f;
			Renderer->ChangeAnimation(GetAnimationName("Run_ScarpUp"));
		}
		else if (GroundType == EGroundType::ScarpDown)
		{
			MoveMaxSpeed = 400.0f;
			Renderer->ChangeAnimation(GetAnimationName("Run_ScarpDown"));
		}
	}
	
	if (IsWallCheck() == true)
	{
		StateChange(EPlayState::Squeeze);
		return;
	}

	if (UEngineInput::IsFree(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT))
	{
		if (MoveVector.Size2D() <= 0.05f)
		{
			Renderer->ChangeAnimation(GetAnimationName("Idle"));
			StateChange(EPlayState::Idle);
			return;
		}
	}

	if (UEngineInput::IsDoubleClick(VK_LEFT, 1.0f) || UEngineInput::IsDoubleClick(VK_RIGHT, 1.0f))
	{
		StateChange(EPlayState::Dash);
		return;
	}

	if (UEngineInput::IsDown('X'))
	{
		StateChange(EPlayState::Jump);
		return;
	}

	if (UEngineInput::IsPress(VK_LEFT))
	{
		if (DirState == PrevDir)
		{
			AddMoveVector(FVector::Left * _DeltaTime);
		}
		else
		{
			MoveVector = FVector::Zero;
			StateChange(EPlayState::Break);
			return;
		}
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		if (DirState == PrevDir)
		{
			AddMoveVector(FVector::Right * _DeltaTime);
		}
		else
		{
			MoveVector = FVector::Zero;
			StateChange(EPlayState::Break);
			return;
		}
	}

	if (UEngineInput::IsPress(VK_DOWN))
	{
		StateChange(EPlayState::Crouch);
		return;
	}

	if (UEngineInput::IsPress(VK_UP))
	{
		StateChange(EPlayState::Fly);
		return;
	}

	MoveUpdate(_DeltaTime, true, true, true);
}

void APlayer::Dash(float _DeltaTime)
{
	EActorDir PrevDir = DirState;
	DirCheck();
	GroundTypeCheck();

	if (GroundType == EGroundType::Flat)
	{
		MoveMaxSpeed = 400.0f;
		Renderer->ChangeAnimation(GetAnimationName("Dash"));
	}
	else if (GroundType == EGroundType::SlopeUp)
	{
		MoveMaxSpeed = 300.0f;
		Renderer->ChangeAnimation(GetAnimationName("Dash"));
	}
	else if (GroundType == EGroundType::SlopeDown)
	{
		MoveMaxSpeed = 450.0f;
		Renderer->ChangeAnimation(GetAnimationName("Dash"));
	}
	else if (GroundType == EGroundType::ScarpUp)
	{
		MoveMaxSpeed = 200.0f;
		Renderer->ChangeAnimation(GetAnimationName("Dash_ScarpUp"));
	}
	else if (GroundType == EGroundType::ScarpDown)
	{
		MoveMaxSpeed = 500.0f;
		Renderer->ChangeAnimation(GetAnimationName("Dash_ScarpDown"));
	}

	if (IsWallCheck() == true)
	{
		StateChange(EPlayState::Squeeze);
		return;
	}

	if (UEngineInput::IsFree(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT))
	{
		if (MoveVector.Size2D() <= 0.05f)
		{
			StateChange(EPlayState::Idle);
			return;
		}
	}

	if (UEngineInput::IsDown(VK_LEFT) || UEngineInput::IsDown(VK_RIGHT))
	{
		if (DirState != PrevDir)
		{
			MoveVector = FVector::Zero;
			StateChange(EPlayState::Break);
			return;
		}
	}

	if (UEngineInput::IsDown('X'))
	{
		StateChange(EPlayState::Jump);
		return;
	}

	if (UEngineInput::IsPress(VK_DOWN))
	{
		StateChange(EPlayState::Crouch);
		return;
	}

	if (UEngineInput::IsPress(VK_UP))
	{
		StateChange(EPlayState::Fly);
		return;
	}

	if (UEngineInput::IsPress(VK_LEFT))
	{
		AddMoveVector(FVector::Left * _DeltaTime);
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		AddMoveVector(FVector::Right * _DeltaTime);
	}

	MoveUpdate(_DeltaTime, true, true, true);
}

void APlayer::Break(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		if (UEngineInput::IsFree(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT))
		{
			StateChange(EPlayState::Idle);
			return;
		}

		if (UEngineInput::IsPress(VK_LEFT) || UEngineInput::IsPress(VK_RIGHT))
		{
 			StateChange(EPlayState::Run);
			return;
		}
	}

	MoveUpdate(_DeltaTime);
}

void APlayer::Jump(float _DeltaTime)
{
	DirCheck();

	if ((JumpVector.Y + GravityVector.Y > 0.0f) || (JumpTimer < 0.0f))
	{
		JumpTimer = 0.3f;
		StateChange(EPlayState::Breakfall);
		return;
	}

	if (UEngineInput::IsPress(VK_LEFT))
	{
		AddMoveVector(FVector::Left * _DeltaTime);
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		AddMoveVector(FVector::Right * _DeltaTime);
	}

	if (UEngineInput::IsFree('X'))
	{
		JumpTimer -= _DeltaTime;
		MoveUpdate(_DeltaTime, true, false, false);
	}
	else
	{
		JumpTimer -= _DeltaTime;
		MoveUpdate(_DeltaTime, false, false, false);
	}

	if (UEngineInput::IsPress(VK_UP) || UEngineInput::IsPress('X'))
	{
		StateChange(EPlayState::Fly);
		return;
	}
}

void APlayer::Breakfall(float _DeltaTime)
{
	DirCheck();
	GroundTypeCheck();
	FVector Pos;

	if (GroundType == EGroundType::Flat)
	{
		Pos = { GetActorLocation().iX() , GetActorLocation().iY() };
	}
	else if (
		GroundType == EGroundType::SlopeUp ||
		GroundType == EGroundType::SlopeDown ||
		GroundType == EGroundType::ScarpUp ||
		GroundType == EGroundType::ScarpDown
		)
	{
		Pos = { GetActorLocation().iX() , GetActorLocation().iY() + 5 };
	}

	if (IsGroundCheck(Pos) == true)
	{
		JumpVector = FVector::Zero;
		Renderer->ChangeAnimation(GetAnimationName("Crouch"));
		
		if (UEngineInput::IsDown('X'))
		{
			StateChange(EPlayState::Jump);
			return;
		}

		if (Renderer->IsCurAnimationEnd() == true)
		{
			StateChange(EPlayState::Run);
			return;
		}
	}

	if (UEngineInput::IsPress(VK_LEFT))
	{
		AddMoveVector(FVector::Left * _DeltaTime);
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		AddMoveVector(FVector::Right * _DeltaTime);
	}

	if (UEngineInput::IsPress(VK_UP) || UEngineInput::IsPress('X'))
	{
		StateChange(EPlayState::Fly);
		return;
	}

    MoveUpdate(_DeltaTime, true, false, false);
}

void APlayer::Fall(float _DeltaTime)
{
	DirCheck();

	if (UEngineInput::IsPress(VK_UP))
	{
		StateChange(EPlayState::Fly);
		return;
	}

	GroundTypeCheck();
	FVector Pos;

	if (GroundType == EGroundType::Flat)
	{
		Pos = { GetActorLocation().iX() , GetActorLocation().iY() };
	}
	else if (
		GroundType == EGroundType::SlopeUp ||
		GroundType == EGroundType::SlopeDown ||
		GroundType == EGroundType::ScarpUp ||
		GroundType == EGroundType::ScarpDown
		)
	{
		Pos = { GetActorLocation().iX() , GetActorLocation().iY() + 5 };
	}

	if (UEngineInput::IsPress(VK_LEFT))
	{
		AddMoveVector(FVector::Left * _DeltaTime);
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		AddMoveVector(FVector::Right * _DeltaTime);
	}

	if (UEngineInput::IsPress(VK_UP) || UEngineInput::IsPress('X'))
	{
		StateChange(EPlayState::Fly);
		return;
	}

	if (IsGroundCheck(Pos) == true)
	{
		JumpVector = FVector::Zero;
		Renderer->ChangeAnimation(GetAnimationName("Crashland"));

		if (Renderer->IsCurAnimationEnd() == true)
		{
			StateChange(EPlayState::Run);
			return;
		}
	}

	MoveUpdate(_DeltaTime, true, false, false);
}

void APlayer::Crouch(float _DeltaTime)
{
	if (UEngineInput::IsFree(VK_DOWN))
	{
		StateChange(EPlayState::Idle);
		return;
	}

	if (UEngineInput::IsDown('X'))
	{

	}

	if (UEngineInput::IsDown('Z'))
	{
		
	}

	MoveUpdate(_DeltaTime);
}

void APlayer::Squeeze(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd() == true)
	{
		Renderer->ChangeAnimation(GetAnimationName("Idle"));
	}

	if (UEngineInput::IsPress(VK_LEFT))
	{
		AddMoveVector(FVector::Left * _DeltaTime);
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		AddMoveVector(FVector::Right * _DeltaTime);
	}

	if (UEngineInput::IsFree(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT))
	{
		StateChange(EPlayState::Idle);
		return;
	}

	if (UEngineInput::IsDown('X'))
	{
		StateChange(EPlayState::Jump);
		return;
	}

	if (UEngineInput::IsPress(VK_DOWN))
	{
		StateChange(EPlayState::Crouch);
		return;
	}

	MoveUpdate(_DeltaTime);
}

void APlayer::Fly(float _DeltaTime)
{
	DirCheck();

	if (UEngineInput::IsDown('Z'))
	{
		StateChange(EPlayState::SpitFly);
		return;
	}

	if (Renderer->IsCurAnimationEnd())
	{
		Renderer->ChangeAnimation(GetAnimationName("Fly"));
	}
	
	if (UEngineInput::IsPress(VK_LEFT))
	{
		AddMoveVector(FVector::Left * _DeltaTime);
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		AddMoveVector(FVector::Right * _DeltaTime);
	}

	if (UEngineInput::IsDown(VK_UP))
	{
		JumpVector = FVector::Up * 300.0f;
		GravityVector = FVector::Zero;
	}

	if (UEngineInput::IsFree(VK_UP))
	{
		FVector Pos = { GetActorLocation().iX(), GetActorLocation().iY() };

		if (IsGroundCheck(Pos) == true)
		{
			JumpVector = FVector::Zero;
			GravityVector = FVector::Zero;
		}
		else
		{
			if (GravityVector.Y > 400.0f)
			{
				GravityVector = FVector::Down * 400.0f;
			}
			else
			{
				GravityVector += GravityAcc * _DeltaTime;
			}
		}
	}

	MoveUpdate(_DeltaTime, false, false, false);
}

void APlayer::SpitFly(float _DeltaTime)
{
	DirCheck();

	if (Renderer->IsCurAnimationEnd())
	{
		MoveMaxSpeed = 300.0f;
		StateChange(EPlayState::Fall);
		return;
	}

	if (UEngineInput::IsDown(VK_UP))
	{
		StateChange(EPlayState::Fly);
		return;
	}

	MoveUpdate(_DeltaTime, true, false, false);
}

void APlayer::IdleStart()
{
	GroundTypeCheck();

	if (GroundType == EGroundType::Flat)
	{
		Renderer->ChangeAnimation(GetAnimationName("Idle"));
	}
	else if (GroundType == EGroundType::SlopeUp)
	{
		Renderer->ChangeAnimation(GetAnimationName("Idle_SlopeUp"));
	}
	else if (GroundType == EGroundType::SlopeDown)
	{
		Renderer->ChangeAnimation(GetAnimationName("Idle_SlopeDown"));
	}
	else if (GroundType == EGroundType::ScarpUp)
	{
		Renderer->ChangeAnimation(GetAnimationName("Idle_ScarpUp"));
	}
	else if (GroundType == EGroundType::ScarpDown)
	{
		Renderer->ChangeAnimation(GetAnimationName("Idle_ScarpDown"));
	}

	DashOff();
	DirCheck();
}

void APlayer::RunStart()
{
	GroundTypeCheck();
	if (
		GroundType == EGroundType::Flat ||
		GroundType == EGroundType::SlopeUp ||
		GroundType == EGroundType::SlopeDown
		)
	{
		Renderer->ChangeAnimation(GetAnimationName("Run"));
	}
	else if (GroundType == EGroundType::ScarpUp)
	{
		Renderer->ChangeAnimation(GetAnimationName("Run_ScarpUp"));
	}
	else if (GroundType == EGroundType::ScarpDown)
	{
		Renderer->ChangeAnimation(GetAnimationName("Run_ScarpDown"));
	}

	DashOff();
	DirCheck();
}

void APlayer::DashStart()
{
	GroundTypeCheck();
	if (
		GroundType == EGroundType::Flat ||
		GroundType == EGroundType::SlopeUp ||
		GroundType == EGroundType::SlopeDown
		)
	{
		Renderer->ChangeAnimation(GetAnimationName("Dash"));
	}
	else if (GroundType == EGroundType::ScarpUp)
	{
		Renderer->ChangeAnimation(GetAnimationName("Dash_ScarpUp"));
	}
	else if (GroundType == EGroundType::ScarpDown)
	{
		Renderer->ChangeAnimation(GetAnimationName("Dash_ScarpDown"));
	}

	DashOn();
	DirCheck();
}

void APlayer::BreakStart()
{
	Renderer->ChangeAnimation(GetAnimationName("Break"));
	DashOff();
	DirCheck();
}

void APlayer::JumpStart()
{
	JumpVector = JumpPower;
	Renderer->ChangeAnimation(GetAnimationName("Jump"));
	DirCheck();
}

void APlayer::BreakfallStart()
{
	Renderer->ChangeAnimation(GetAnimationName("Breakfall"));
	DirCheck();
}

void APlayer::FallStart()
{
	Renderer->ChangeAnimation(GetAnimationName("Fall"));
	DashOff();
	DirCheck();
}

void APlayer::CrouchStart()
{
	GroundTypeCheck();

	if (GroundType == EGroundType::Flat)
	{
		Renderer->ChangeAnimation(GetAnimationName("Crouch"));
	}
	else if (GroundType == EGroundType::SlopeUp)
	{
		Renderer->ChangeAnimation(GetAnimationName("Crouch_SlopeUp"));
	}
	else if (GroundType == EGroundType::SlopeDown)
	{
		Renderer->ChangeAnimation(GetAnimationName("Crouch_SlopeDown"));
	}
	else if (GroundType == EGroundType::ScarpUp)
	{
		Renderer->ChangeAnimation(GetAnimationName("Crouch_ScarpUp"));
	}
	else if (GroundType == EGroundType::ScarpDown)
	{
		Renderer->ChangeAnimation(GetAnimationName("Crouch_ScarpDown"));
	}

	DashOff();
	DirCheck();
}

void APlayer::SqueezeStart()
{
	Renderer->ChangeAnimation(GetAnimationName("Squeeze"));
	DashOff();
	DirCheck();
}

void APlayer::FlyStart()
{
	MoveMaxSpeed = 200.0f;
	JumpPower = FVector::Up * 300.0f;

	JumpVector = JumpPower;
	GravityVector = FVector::Zero;
	Renderer->ChangeAnimation(GetAnimationName("Absorb_Fly"));
	DashOff();
	DirCheck();
}

void APlayer::SpitFlyStart()
{
	Renderer->ChangeAnimation(GetAnimationName("Spit_Fly"));
	DashOff();
	DirCheck();
}

void APlayer::AddMoveVector(const FVector& _DirDelta)
{
	MoveVector += _DirDelta * MoveAcc;
}

void APlayer::CalMoveVector(float _DeltaTime)
{
	if (IsWallCheck() == true)
	{
		MoveVector = FVector::Zero;
	}

	if (UEngineInput::IsFree(VK_LEFT) == true && UEngineInput::IsFree(VK_RIGHT) == true)
	{
		if (MoveVector.Size2D() >= 0.001)
		{
			MoveVector += (-MoveVector.Normalize2DReturn()) * _DeltaTime * MoveAcc;
		}
		else
		{
			MoveVector = float4::Zero;
		}
	}

	if (MoveVector.Size2D() >= MoveMaxSpeed)
	{
		MoveVector = MoveVector.Normalize2DReturn() * MoveMaxSpeed;
	}
}

void APlayer::CalGravityVector(float _DeltaTime)
{
	GravityVector += GravityAcc * _DeltaTime;

	FVector Pos = { GetActorLocation().iX(), GetActorLocation().iY()};
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

void APlayer::CalLastMoveVector(float _DeltaTime)
{
	LastMoveVector = FVector::Zero;
	LastMoveVector = LastMoveVector + MoveVector;
	LastMoveVector = LastMoveVector + JumpVector;
	LastMoveVector = LastMoveVector + GravityVector;
}

void APlayer::MoveLastMoveVector(float _DeltaTime)
{
	float Pos = GetActorLocation().X;
	float WindowHalfSize = GEngine->MainWindow.GetWindowScale().hX();
	float MapSize = UContentsHelper::ColMapImage->GetScale().X;

	if (Pos > WindowHalfSize && Pos < (MapSize - WindowHalfSize))
	{
		GetWorld()->AddCameraPos(MoveVector * _DeltaTime);
	}

	AddActorLocation(LastMoveVector * _DeltaTime);
}

void APlayer::GroundUp()
{
	if (
		State == EPlayState::Jump ||
		State == EPlayState::Breakfall ||
		State == EPlayState::Fall
		)
	{
		return;
	}

	while (true)
	{
		FVector LeftPos = { GetActorLocation().iX() - 1, GetActorLocation().iY() -2};
		FVector RightPos = { GetActorLocation().iX() + 1, GetActorLocation().iY() -2};
		
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

void APlayer::GroundDown()
{
	if (
		State == EPlayState::Jump ||
		State == EPlayState::Breakfall ||
		State == EPlayState::Fall
		)
	{
		return;
	}

	if (GroundType == EGroundType::Flat)
	{
		return;
	}

	while (true)
	{
		FVector LeftPos = { GetActorLocation().iX() - 1, GetActorLocation().iY() + 2 };
		FVector RightPos = { GetActorLocation().iX() + 1, GetActorLocation().iY() + 2 };

		if (IsGroundCheck(LeftPos) == false  && IsGroundCheck(RightPos) == false)
		{
			bool b1 = IsGroundCheck(LeftPos); 
			bool b2 = IsGroundCheck(RightPos);
			AddActorLocation(FVector::Down);
		}
		else
		{
			break;
		}
	}
}
 
void APlayer::MoveUpdate(float _DeltaTime, bool _IsGravity, bool _IsGroundUp, bool _IsGroundDown)
{
	GroundTypeCheck();

	CalMoveVector(_DeltaTime);
	if (_IsGravity == true)
	{
		CalGravityVector(_DeltaTime);
	}
	CalLastMoveVector(_DeltaTime);
	MoveLastMoveVector(_DeltaTime);
	if (_IsGroundUp == true)
	{
		GroundUp();
	}
	if (_IsGroundDown == true)
	{
 		GroundDown();
	}
}