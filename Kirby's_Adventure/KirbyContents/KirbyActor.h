#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class AKirbyActor : public AActor
{
public:
	AKirbyActor();
	~AKirbyActor();

	AKirbyActor(const AKirbyActor& _Other) = delete;
	AKirbyActor(AKirbyActor&& _Other) noexcept = delete;
	AKirbyActor& operator=(const AKirbyActor& _Other) = delete;
	AKirbyActor& operator=(AKirbyActor&& _Other) noexcept = delete;

	EActorType GetActorType() const
	{
		return ActorType;
	}

	void SetActorType(EActorType _ActorType)
	{
		ActorType = _ActorType;
	}

protected:
	EActorType ActorType = EActorType::None;

private:

};