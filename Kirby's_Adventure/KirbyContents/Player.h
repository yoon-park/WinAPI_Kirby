#pragma once
#include <EngineCore\Actor.h>
#include "ContentsHelper.h"

class APlayer : public AActor
{
public:
	APlayer();
	~APlayer();

	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	static APlayer* GetMainPlayer();

protected:
	EPlayState State = EPlayState::None;
	EActorDir DirState = EActorDir::Right;
	EGroundType GroundType = EGroundType::None;
	std::string CurAnimationName = "None";

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	std::string GetAnimationName(std::string _Name);

	void DirCheck();
	void GroundTypeCheck();
	bool IsGroundCheck(FVector _Pos);
	bool IsWallCheck();
	bool IsLeftWallCheck();
	bool IsRightWallCheck();
	void DashOn();
	void DashOff();

	void StateUpdate(float _DeltaTime);
	void StateChange(EPlayState _State);

	void CameraFreeMove(float _DeltaTime);
	void FreeMove(float _DeltaTime);

	void Idle(float _DeltaTime);
	void Run(float _DeltaTime);
	void Dash(float _DeltaTime);
	void Break(float _DeltaTime);
	void Jump(float _DeltaTime);
	void Breakfall(float _DeltaTime);
	void Fall(float _DeltaTime);
	void Crouch(float _DeltaTime);
	void Squeeze(float _DeltaTime);

	void IdleStart();
	void RunStart();
	void DashStart();
	void BreakStart();
	void JumpStart();
	void BreakfallStart();
	void FallStart();
	void CrouchStart();
	void SqueezeStart();

private:
	UCollision* BodyCollision = nullptr;
	UImageRenderer* Renderer = nullptr;
	float AnimationTime = 0.0f;
	int AnimationFrame = 0;

	FVector MoveVector = FVector::Zero;
	FVector MoveAcc = FVector::Right * 1000.0f;
	float MoveMaxSpeed = 300.0f;
	float FreeMoveSpeed = 1000.0f;

	FVector GravityVector = FVector::Zero;
	FVector GravityAcc = FVector::Down * 3000.0f;

	FVector JumpVector = FVector::Zero;
	FVector JumpPower = FVector::Up * 510.0f;
	float JumpTimer = 0.3f;

	FVector LastMoveVector = FVector::Zero;

	static APlayer* MainPlayer;

	void AddMoveVector(const FVector& _DirDelta);
	void CalMoveVector(float _DeltaTime);
	void CalGravityVector(float _DeltaTime);
	void CalLastMoveVector(float _DeltaTime);
	void MoveLastMoveVector(float _DeltaTime);
	void GroundUp();
	void GroundDown();
	void MoveUpdate(float _DeltaTime, bool _IsGravity = true, bool _IsGroundUp = true, bool _IsGroundDown = false);
};