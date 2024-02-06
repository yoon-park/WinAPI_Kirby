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

protected:
	EPlayState State = EPlayState::None;
	EActorDir DirState = EActorDir::Right;
	std::string CurAnimationName = "None";

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void DirCheck();
	void GravityCheck(float _DeltaTime);
	std::string GetAnimationName(std::string _Name);
	
	void StateUpdate(float _DeltaTime);
	void StateChange(EPlayState _State);

	void CameraFreeMove(float _DeltaTime);
	void FreeMove(float _DeltaTime);

	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);
	void Jump(float _DeltaTime);

	void IdleStart();
	void MoveStart();
	void JumpStart();

private:
	bool Dir = false;
	float Gravity = 500.0f;
	float MoveSpeed = 500.0f;
	float FreeMoveSpeed = 1000.0f;

	float AnimationTime = 0.0f;
	int AnimationFrame = 0;
	UImageRenderer* Renderer;
};