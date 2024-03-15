#pragma once
#include "Monster.h"

class ATogezo : public AMonster
{
public:
	ATogezo();
	~ATogezo();

	ATogezo(const ATogezo& _Other) = delete;
	ATogezo(ATogezo&& _Other) noexcept = delete;
	ATogezo& operator=(const ATogezo& _Other) = delete;
	ATogezo& operator=(ATogezo&& _Other) noexcept = delete;

protected:
	float AnimationTimer = 0.0f;
	int AnimationCount = 0;
	bool IsStop = false;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void MoveStart() override;
	void JumpStart() override;
	void BreakfallStart() override;
	void AttackStart() override;
	void Move(float _DeltaTime) override;
	void Jump(float _DeltaTime) override;
	void Breakfall(float _DeltaTime) override;
	void Attack(float _DeltaTime) override;

	void DirCheck() override;

	void SetAnimationTimer(float _AnimationTimer);
	void SetAnimationCount(int _AnimationCount);

private:

};