#pragma once
#include "Monster.h"

class ASparky : public AMonster
{
public:
	ASparky();
	~ASparky();

	ASparky(const ASparky& _Other) = delete;
	ASparky(ASparky&& _Other) noexcept = delete;
	ASparky& operator=(const ASparky& _Other) = delete;
	ASparky& operator=(ASparky&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void IdleStart() override;
	void JumpStart() override;
	void BreakfallStart() override;
	void FallStart() override;
	void AttackStart() override;
	void Idle(float _DeltaTime) override;
	void Jump(float _DeltaTime) override;
	void Breakfall(float _DeltaTime) override;
	void Fall(float _DeltaTime) override;
	void Attack(float _DeltaTime) override;

	void DirCheck() override;

private:

};