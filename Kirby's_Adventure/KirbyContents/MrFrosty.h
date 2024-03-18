#pragma once
#include "Monster.h"

class AMrFrosty : public AMonster
{
public:
	AMrFrosty();
	~AMrFrosty();

	AMrFrosty(const AMrFrosty& _Other) = delete;
	AMrFrosty(AMrFrosty&& _Other) noexcept = delete;
	AMrFrosty& operator=(const AMrFrosty& _Other) = delete;
	AMrFrosty& operator=(AMrFrosty&& _Other) noexcept = delete;

protected:
	float AnimationTimer = 0.0f;
	int AnimationCount = 0;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void IdleStart() override;
	void MoveStart() override;
	void AttackStart() override;
	void DeadStart() override;
	void Idle(float _DeltaTime) override;
	void Move(float _DeltaTime) override;
	void Attack(float _DeltaTime) override;
	void Dead(float _DeltaTime) override;

	void DirCheck() override;

	void SetAnimationTimer(float _AnimationTimer);
	void SetAnimationCount(int _AnimationCount);

private:

};