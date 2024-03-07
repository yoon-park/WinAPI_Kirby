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
	UImageRenderer* Renderer = nullptr;
	UCollision* AttackCollision = nullptr;

	EActorDir DirState = EActorDir::Right;
	std::string CurAnimationName = "None";
	
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void DirCheck();
	virtual bool IsWallCheck();
	std::string GetAnimationName(std::string _Name);

private:

};