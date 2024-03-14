#pragma once
#include "KirbyActor.h"
#include "ContentsHelper.h"

class AMonster : public AKirbyActor
{
public:
	AMonster();
	~AMonster();

	AMonster(const AMonster& _Other) = delete;
	AMonster(AMonster&& _Other) noexcept = delete;
	AMonster& operator=(const AMonster& _Other) = delete;
	AMonster& operator=(AMonster&& _Other) noexcept = delete;

	EActorDir GetDirState() const;
	EAbiltyType GetAbility() const;

protected:
	EActorDir DirState = EActorDir::Left;
	EActorDir UpDownDirState = EActorDir::Down;
	EMonsterState State = EMonsterState::None;
	EGroundType GroundType = EGroundType::None;
	EAbiltyType Ability = EAbiltyType::None;
	std::string CurAnimationName = "None";

	UImageRenderer* Renderer = nullptr;
	UImageRenderer* AttackRenderer = nullptr;
	UCollision* BodyCollision = nullptr;
	UCollision* DetectCollision = nullptr;
	UCollision* AttackCollision = nullptr;

	float MoveTimer = 0.0f;
	FVector MoveAcc = FVector::Right * 300.0f;
	FVector UpDownMoveAcc = FVector::Down * 1000.0f;
	float MoveMaxSpeed = 100.0f;
	FVector JumpPower = FVector::Up * 500.0f;
	FVector GravityAcc = FVector::Down * 2000.0f;
	float GravityMaxSpeed = 1500.0f;
	float AttackTimer = 0.0f;

	FVector MoveVector = FVector::Zero;
	FVector JumpVector = FVector::Zero;
	FVector GravityVector = FVector::Zero;
	FVector LastMoveVector = FVector::Zero;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateChange(EMonsterState _State);
	void StateUpdate(float _DeltaTime);

	void AddMoveVector(const FVector& _DirDelta);
	void AddUpDownMoveVector(const FVector& _DirDelta);
	void MoveUpdate(float _DeltaTime, bool _IsGravity, bool _IsGroundUp, bool _IsGroundDown);

	virtual void IdleStart();
	virtual void MoveStart();
	virtual void JumpStart();
	virtual void BreakfallStart();
	virtual void FallStart();
	virtual void AttackStart();
	virtual void AbsorbStart();

	virtual void Idle(float _DeltaTime);
	virtual void Move(float _DeltaTime);
	virtual void Jump(float _DeltaTime);
	virtual void Breakfall(float _DeltaTime);
	virtual void Fall(float _DeltaTime);
	virtual void Attack(float _DeltaTime);
	virtual void Absorb(float _DeltaTime);

	virtual void DirCheck();
	virtual void UpDownDirCheck();
	void GroundTypeCheck();
	bool IsGroundCheck(FVector _Pos);
	bool IsWallCheck();
	bool AbsorbCheck();
	bool DetectCheck();
	std::string GetAnimationName(std::string _Name);

	void SetAbility(EAbiltyType _Ability);
	void SetMoveTimer(float _MoveTimer);
	void SetMoveMaxSpeed(float _MoveMaxSpeed);
	void SetJumpPower(FVector _JumpPower);
	void SetAttackTimer(float _AttackTimer);

private:

};