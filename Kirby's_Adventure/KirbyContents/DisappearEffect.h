#pragma once
#include "Effect.h"

class ADisappearEffect : public AEffect
{
public:
	ADisappearEffect();
	~ADisappearEffect();

	ADisappearEffect(const ADisappearEffect& _Other) = delete;
	ADisappearEffect(ADisappearEffect&& _Other) noexcept = delete;
	ADisappearEffect& operator=(const ADisappearEffect& _Other) = delete;
	ADisappearEffect& operator=(ADisappearEffect&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};