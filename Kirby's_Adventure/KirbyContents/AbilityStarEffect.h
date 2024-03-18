#pragma once
#include "Effect.h"

class AAbilityStarEffect : public AEffect
{
public:
	AAbilityStarEffect();
	~AAbilityStarEffect();

	AAbilityStarEffect(const AAbilityStarEffect& _Other) = delete;
	AAbilityStarEffect(AAbilityStarEffect&& _Other) noexcept = delete;
	AAbilityStarEffect& operator=(const AAbilityStarEffect& _Other) = delete;
	AAbilityStarEffect& operator=(AAbilityStarEffect&& _Other) noexcept = delete;

	void SetEffectDirNormal(FVector _EffectDirNormal);

protected:
	float AnimationTimer = 2.0;
	FVector EffectDirNormal = FVector::Zero;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};