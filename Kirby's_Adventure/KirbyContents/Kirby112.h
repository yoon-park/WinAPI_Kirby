#pragma once
#include "Player.h"

class AKirby112 : public APlayer
{
public:
	AKirby112();
	~AKirby112();

	AKirby112(const AKirby112& _Other) = delete;
	AKirby112(AKirby112&& _Other) noexcept = delete;
	AKirby112& operator=(const AKirby112& _Other) = delete;
	AKirby112& operator=(AKirby112&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void IntoDoor() override;

private:

};