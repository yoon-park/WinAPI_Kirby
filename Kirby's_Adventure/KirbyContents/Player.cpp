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
		Renderer->SetTransform({ {0,0}, {128, 128} });

		Renderer->CreateAnimation("Idle_Right", "Kirby_Right.png", 0, 1, 0.5f, true);
		Renderer->CreateAnimation("Run_Right", "Kirby_Right.png", 2, 5, 0.1f, true);
		Renderer->CreateAnimation("Jump_Right", "Kirby_Right.png", 9, 13, 0.1f, true);
		Renderer->CreateAnimation("Crouch_Right", "Kirby_Right.png", 7, 7, 0.1f, true);
		Renderer->CreateAnimation("Squeeze_Right", "Kirby_Right.png", 6, 6, 0.1f, false);

		Renderer->CreateAnimation("Idle_Left", "Kirby_Left.png", 0, 1, 0.5f, true);
		Renderer->CreateAnimation("Run_Left", "Kirby_Left.png", 2, 5, 0.1f, true);
		Renderer->CreateAnimation("Jump_Left", "Kirby_Left.png", 9, 13, 0.1f, true);
		Renderer->CreateAnimation("Crouch_Left", "Kirby_Left.png", 7, 7, 0.1f, true);
		Renderer->CreateAnimation("Squeeze_Left", "Kirby_Left.png", 6, 6, 0.1f, false);
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
	case EPlayState::Jump:
		Jump(_DeltaTime);
		break;
	case EPlayState::Crouch:
		Crouch(_DeltaTime);
		break;
	case EPlayState::Squeeze:
		Squeeze(_DeltaTime);
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
		case EPlayState::Jump:
			JumpStart();
			break;
		case EPlayState::Crouch:
			CrouchStart();
			break;
		case EPlayState::Squeeze:
			SqueezeStart();
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
	FVector FreeMove = FVector::Zero;

	if (UEngineInput::IsDown('1'))
	{
		StateChange(EPlayState::Idle);
		return;
	}

	if (UEngineInput::IsPress(VK_LEFT))
	{
		FreeMove += FVector::Left * _DeltaTime * FreeMoveSpeed;
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		FreeMove += FVector::Right * _DeltaTime * FreeMoveSpeed;
	}

	if (UEngineInput::IsPress(VK_UP))
	{
		FreeMove += FVector::Up * _DeltaTime * FreeMoveSpeed;
	}

	if (UEngineInput::IsPress(VK_DOWN))
	{
		FreeMove += FVector::Down * _DeltaTime * FreeMoveSpeed;
	}

	AddActorLocation(FreeMove * _DeltaTime);
	GetWorld()->AddCameraPos(FreeMove * _DeltaTime);
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

	if (UEngineInput::IsDown(VK_SPACE))
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

void APlayer::Run(float _DeltaTime)
{
	DirCheck();

	if (IsWallCheck() == true)
	{
		StateChange(EPlayState::Squeeze);
		return;
	}

	if (UEngineInput::IsFree(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT))
	{
		if (MoveVector.Size2D() <= 0.06f)
		{
			StateChange(EPlayState::Idle);
			return;
		}
	}

	if (UEngineInput::IsDown(VK_SPACE))
	{
		StateChange(EPlayState::Jump);
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

	if (UEngineInput::IsPress(VK_DOWN))
	{
		StateChange(EPlayState::Crouch);
		return;
	}

	MoveUpdate(_DeltaTime);
}

void APlayer::Jump(float _DeltaTime)
{
	DirCheck();

	if (UEngineInput::IsPress(VK_LEFT))
	{
		AddMoveVector(FVector::Left * _DeltaTime);
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		AddMoveVector(FVector::Right * _DeltaTime);
	}

	MoveUpdate(_DeltaTime);

	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		JumpVector = FVector::Zero;
		StateChange(EPlayState::Idle);
		return;
	}
}

void APlayer::Crouch(float _DeltaTime)
{
	if (UEngineInput::IsFree(VK_DOWN))
	{
		StateChange(EPlayState::Idle);
		return;
	}

	if (UEngineInput::IsDown(VK_SPACE))
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

	if (UEngineInput::IsDown(VK_SPACE))
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

void APlayer::IdleStart()
{
	Renderer->ChangeAnimation(GetAnimationName("Idle"));
	DirCheck();
}

void APlayer::RunStart()
{
	Renderer->ChangeAnimation(GetAnimationName("Run"));
	DirCheck();
}

void APlayer::JumpStart()
{
	JumpVector = JumpPower;
	Renderer->ChangeAnimation(GetAnimationName("Jump"));
	DirCheck();
}

void APlayer::CrouchStart()
{
	Renderer->ChangeAnimation(GetAnimationName("Crouch"));
	DirCheck();
}

void APlayer::SqueezeStart()
{
	Renderer->ChangeAnimation(GetAnimationName("Squeeze"));
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

	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		GravityVector = FVector::Zero;
	}
}

void APlayer::CalJumpVector(float _DeltaTime)
{

}

void APlayer::CalLastMoveVector(float _DeltaTime)
{
	LastMoveVector = FVector::Zero;
	LastMoveVector = LastMoveVector + MoveVector;
	LastMoveVector = LastMoveVector + JumpVector;
	LastMoveVector = LastMoveVector + GravityVector;
	LastMoveVector + JumpVector;
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
	while (true)
	{
		Color8Bit Color_L = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX() - 5, GetActorLocation().iY() - 1, Color8Bit::MagentaA);
		Color8Bit Color_R = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX() + 5, GetActorLocation().iY() - 1, Color8Bit::MagentaA);
		if (Color_L == Color8Bit(255, 0, 255, 0) || Color_R == Color8Bit(255, 0, 255, 0))
		{
			AddActorLocation(FVector::Up);
		}
		else
		{
			break;
		}
	}
}

void APlayer::MoveUpdate(float _DeltaTime)
{
	CalMoveVector(_DeltaTime);
	CalGravityVector(_DeltaTime);
	CalLastMoveVector(_DeltaTime);
	MoveLastMoveVector(_DeltaTime);
	GroundUp();
}