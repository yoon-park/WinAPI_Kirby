#pragma once
#include <EngineCore\Actor.h>
#include "ContentsHelper.h"

class AMonster : public AActor
{
public:
	AMonster();
	~AMonster();

	AMonster(const AMonster& _Other) = delete;
	AMonster(AMonster&& _Other) noexcept = delete;
	AMonster& operator=(const AMonster& _Other) = delete;
	AMonster& operator=(AMonster&& _Other) noexcept = delete;

protected:
	EActorDir DirState = EActorDir::Right;
	EMonsterState State = EMonsterState::None;
	EAbiltyType Ability = EAbiltyType::None;
	std::string CurAnimationName = "None";

	UImageRenderer* Renderer = nullptr;
	UCollision* BodyCollision = nullptr;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	std::string GetAnimationName(std::string _Name);
	void DirCheck();
	void StateUpdate(float _DeltaTime);
	void StateChange(EPlayState _State);

private:

};