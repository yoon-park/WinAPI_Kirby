#pragma once
#include "KirbyActor.h"
#include "ContentsHelper.h"

class APlayer : public AKirbyActor
{
public:
	APlayer();
	~APlayer();

	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	static APlayer* GetMainPlayer();

	EActorDir GetDirState() const;
	bool GetAbsorbActive() const;
	FVector GetLocationDifference() const;

	void SetCreateEffectTimer(float _CreateEffectTimer);

protected:
	EActorDir DirState = EActorDir::Right;
	EPlayState State = EPlayState::None;
	EAbiltyType Ability_Absorb = EAbiltyType::None;
	EAbiltyType Ability_Active = EAbiltyType::None;
	EGroundType GroundType = EGroundType::None;
	std::string CurAnimationName = "None";

	bool IsAbsorb = false;
	bool AbsorbActive = false;
	bool IsCrashland = false;
	float CreateEffectTimer = 0.07f;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void DirCheck();
	void GroundTypeCheck();
	bool IsGroundCheck(FVector _Pos);
	bool IsCeilingCheck(FVector _Pos);
	bool IsWallCheck();
	bool IsLeftWallCheck();
	bool IsRightWallCheck();
	bool IsDoorCheck();
	void DashOn();
	void DashOff();
	std::string GetAnimationName(std::string _Name);

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
	void Slide(float _DeltaTime);
	void Squeeze(float _DeltaTime);
	void Fly(float _DeltaTime);
	void SpitFly(float _DeltaTime);
	void Absorb(float _DeltaTime);
	void Digest(float _DeltaTime);
	void Spit(float _DeltaTime);
	void Attack(float _DeltaTime);
	void Door(float _DeltaTime);

	void IdleStart();
	void RunStart();
	void DashStart();
	void BreakStart();
	void JumpStart();
	void BreakfallStart();
	void FallStart();
	void CrouchStart();
	void SlideStart();
	void SqueezeStart();
	void FlyStart();
	void SpitFlyStart();
	void AbsorbStart();
	void DigestStart();
	void SpitStart();
	void AttackStart();
	void DoorStart();

private:
	UCollision* BodyCollision = nullptr;
	UCollision* AbsorbCollision0 = nullptr;
	UCollision* AbsorbCollision1 = nullptr;
	UCollision* AbsorbCollision2 = nullptr;
	UCollision* AbsorbCollision3 = nullptr;
	UCollision* AttackCollision = nullptr;
	UImageRenderer* Renderer = nullptr;
	float AnimationTime = 0.0f;
	int AnimationFrame = 0;

	FVector MoveVector = FVector::Zero;
	FVector MoveAcc = FVector::Right * 1000.0f;
	float MoveMaxSpeed = 300.0f;
	float FreeMoveSpeed = 1000.0f;
	FVector GravityVector = FVector::Zero;
	FVector GravityAcc = FVector::Down * 2500.0f;
	float GravityMaxSpeed = 1500.0f;
	FVector JumpVector = FVector::Zero;
	FVector JumpPower = FVector::Up * 510.0f;
	float JumpTimer = 0.2f;
	FVector LastMoveVector = FVector::Zero;

	FVector LocationDifference = FVector::Zero;

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