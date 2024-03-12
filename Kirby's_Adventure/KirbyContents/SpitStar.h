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

	void SetDirState(EActorDir _DirState) override;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	bool IsWallCheck() override;

private:
	FVector MoveVector = FVector::Zero;
	FVector MovePower = FVector::Zero;
	float Timer = 0.2f;
};