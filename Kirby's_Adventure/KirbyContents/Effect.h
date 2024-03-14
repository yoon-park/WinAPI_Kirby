#pragma once
#include "KirbyActor.h"

class AEffect : public AKirbyActor
{
public:
	AEffect();
	~AEffect();

	AEffect(const AEffect& _Other) = delete;
	AEffect(AEffect&& _Other) noexcept = delete;
	AEffect& operator=(const AEffect& _Other) = delete;
	AEffect& operator=(AEffect&& _Other) noexcept = delete;

	void SetOwner(AKirbyActor* _Owner)
	{
		Owner = _Owner;
	}

	virtual void SetDirState(EActorDir _DirState);

protected:
	UImageRenderer* Renderer = nullptr;
	UCollision* EffectCollision = nullptr;
	AKirbyActor* Owner = nullptr;
	EActorDir DirState = EActorDir::Right;
	std::string CurAnimationName = "None";
	FVector MoveVector = FVector::Zero;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void DirCheck();
	std::string GetAnimationName(std::string _Name);

private:

};