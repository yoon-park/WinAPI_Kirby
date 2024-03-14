#pragma once
#include "Monster.h"

class AHotHead : public AMonster
{
public:
	AHotHead();
	~AHotHead();

	AHotHead(const AHotHead& _Other) = delete;
	AHotHead(AHotHead&& _Other) noexcept = delete;
	AHotHead& operator=(const AHotHead& _Other) = delete;
	AHotHead& operator=(AHotHead&& _Other) noexcept = delete;

protected:
	float AnimationTimer = 0.0f;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void IdleStart() override;
	void MoveStart() override;
	void AttackStart() override;
	void Idle(float _DeltaTime) override;
	void Move(float _DeltaTime) override;
	void Attack(float _DeltaTime) override;

	void DirCheck() override;

	void SetAnimationTimer(float _AnimationTimer);

private:

};