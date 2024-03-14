#pragma once
#include "Effect.h"

class AAbsorbEffect : public AEffect
{
public:
	AAbsorbEffect();
	~AAbsorbEffect();

	AAbsorbEffect(const AAbsorbEffect& _Other) = delete;
	AAbsorbEffect(AAbsorbEffect&& _Other) noexcept = delete;
	AAbsorbEffect& operator=(const AAbsorbEffect& _Other) = delete;
	AAbsorbEffect& operator=(AAbsorbEffect&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};