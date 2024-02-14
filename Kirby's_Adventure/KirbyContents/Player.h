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
	std::string CurAnimationName = "None";

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	std::string GetAnimationName(std::string _Name);

	void DirCheck();
	void StateUpdate(float _DeltaTime);
	void StateChange(EPlayState _State);

	void CameraFreeMove(float _DeltaTime);
	void FreeMove(float _DeltaTime);

	void Idle(float _DeltaTime);
	void Run(float _DeltaTime);
	void Jump(float _DeltaTime);

	void IdleStart();
	void RunStart();
	void JumpStart();

private:
	float AnimationTime = 0.0f;
	int AnimationFrame = 0;
	UImageRenderer* Renderer;

	bool Dir = false;
	float FreeMoveSpeed = 1000.0f;

	FVector MoveVector = FVector::Zero;
	FVector MoveAcc = FVector::Right * 500.0f;
	float MoveMaxSpeed = 500.0f;

	FVector GravityVector = FVector::Zero;
	FVector GravityAcc = FVector::Down * 2000.0f;

	FVector JumpVector = FVector::Zero;
	FVector JumpPower = FVector::Up * 1000;

	FVector LastMoveVector = FVector::Zero;

	static APlayer* MainPlayer;

	void AddMoveVector(const FVector& _DirDelta);
	void CalMoveVector(float _DeltaTime);
	void CalGravityVector(float _DeltaTime);
	void CalJumpVector(float _DeltaTime);
	void CalLastMoveVector(float _DeltaTime);
	void MoveLastMoveVector(float _DeltaTime);
	void MoveUpdate(float _DeltaTime);
};