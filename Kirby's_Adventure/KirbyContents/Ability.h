#pragma once
#include "KirbyActor.h"

class AAbility : public AKirbyActor
{
public:
	AAbility();
	~AAbility();

	AAbility(const AAbility& _Other) = delete;
	AAbility(AAbility&& _Other) noexcept = delete;
	AAbility& operator=(const AAbility& _Other) = delete;
	AAbility& operator=(AAbility&& _Other) noexcept = delete;

	void SetOwner(AKirbyActor* _Owner)
	{
		Owner = _Owner;
	}

	virtual void SetDirState(EActorDir _DirState);

protected:
	UImageRenderer* Renderer = nullptr;
	UCollision* AttackCollision = nullptr;
	AKirbyActor* Owner = nullptr;
	EActorDir DirState = EActorDir::Right;
	std::string CurAnimationName = "None";
	
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void DirCheck();
	virtual bool IsWallCheck();
	void AttackCheck();
	std::string GetAnimationName(std::string _Name);

private:

};