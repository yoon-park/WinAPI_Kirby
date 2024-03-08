#pragma once
#include "Ability.h"

class ABurp : public AAbility
{
public:
	ABurp();
	~ABurp();

	ABurp(const ABurp& _Other) = delete;
	ABurp(ABurp&& _Other) noexcept = delete;
	ABurp& operator=(const ABurp& _Other) = delete;
	ABurp& operator=(ABurp&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	bool IsWallCheck() override;

private:
	FVector MoveVector = FVector::Zero;
	FVector MovePower = FVector::Zero;
	FVector MoveAcc = FVector::Zero;
};