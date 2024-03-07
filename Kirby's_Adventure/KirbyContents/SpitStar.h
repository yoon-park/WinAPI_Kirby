#pragma once
#include "Ability.h"

class ASpitStar : public AAbility
{
public:
	ASpitStar();
	~ASpitStar();

	ASpitStar(const ASpitStar& _Other) = delete;
	ASpitStar(ASpitStar&& _Other) noexcept = delete;
	ASpitStar& operator=(const ASpitStar& _Other) = delete;
	ASpitStar& operator=(ASpitStar&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	bool IsWallCheck() override;

private:
	FVector MoveVector = FVector::Zero;
	FVector MovePower = FVector::Right * 1000.0f;
	FVector MoveAcc = FVector::Left * 2500.0f;
	float Timer = 0.2f;
};