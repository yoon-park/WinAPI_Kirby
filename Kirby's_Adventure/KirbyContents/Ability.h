#pragma once
#include <EngineCore/Actor.h>
#include "Player.h"

class AAbility : public AActor
{
public:
	AAbility();
	~AAbility();

	AAbility(const AAbility& _Other) = delete;
	AAbility(AAbility&& _Other) noexcept = delete;
	AAbility& operator=(const AAbility& _Other) = delete;
	AAbility& operator=(AAbility&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UImageRenderer* Renderer = nullptr;
	UCollision* AttackCollision = nullptr;

private:

};