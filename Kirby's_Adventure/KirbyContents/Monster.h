#pragma once
#include <EngineCore\Actor.h>
#include "ContentsHelper.h"

class AMonster : public AActor
{
public:
	AMonster();
	~AMonster();

	AMonster(const AMonster& _Other) = delete;
	AMonster(AMonster&& _Other) noexcept = delete;
	AMonster& operator=(const AMonster& _Other) = delete;
	AMonster& operator=(AMonster&& _Other) noexcept = delete;

protected:
	EActorDir DirState = EActorDir::Left;
	EMonsterState State = EMonsterState::None;
	EAbiltyType Ability = EAbiltyType::None;
	std::string CurAnimationName = "None";

	UImageRenderer* Renderer = nullptr;
	UCollision* BodyCollision = nullptr;

	FVector MoveVector = FVector::Zero;
	FVector MovePower = FVector::Zero;
	FVector MoveAcc = FVector::Zero;
	FVector JumpPower = FVector::Zero;
	FVector GravityAcc = FVector::Zero;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void StateChange(EMonsterState _State);
	void StateUpdate(float _DeltaTime);

	virtual void MoveStart();
	virtual void AttackStart();
	virtual void AbsorbStart();

	virtual void Move(float _DeltaTime);
	virtual void Attack(float _DeltaTime);
	virtual void Absorb(float _DeltaTime);

	void DirCheck();
	bool AbsorbCheck();
	std::string GetAnimationName(std::string _Name);

private:

};