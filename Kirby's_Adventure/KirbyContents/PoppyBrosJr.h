#pragma once
#include "Monster.h"

class APoppyBrosJr : public AMonster
{
public:
	APoppyBrosJr();
	~APoppyBrosJr();

	APoppyBrosJr(const APoppyBrosJr& _Other) = delete;
	APoppyBrosJr(APoppyBrosJr&& _Other) noexcept = delete;
	APoppyBrosJr& operator=(const APoppyBrosJr& _Other) = delete;
	APoppyBrosJr& operator=(APoppyBrosJr&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void JumpStart() override;
	void BreakfallStart() override;
	void Jump(float _DeltaTime) override;
	void Breakfall(float _DeltaTime) override;

	void DirCheck() override;

private:

};