#pragma once
#include <map>
#include <list>

#include "NameObject.h"

class AActor;
class EngineCore;
class UImageRenderer;

class ULevel : public UNameObject
{
	friend EngineCore;
	friend UImageRenderer;

public:
	ULevel();
	~ULevel();

	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);

	template<typename ActorType>
	ActorType* SpawnActor(int _Order = 0)
	{
		ActorType* NewActor = new ActorType();
		ActorInit(NewActor);
		AllActor[_Order].push_back(NewActor);
		return NewActor;
	}

protected:

private:
	std::map<int, std::list<AActor*>> AllActor;
	std::map<int, std::list<UImageRenderer*>> Renderers;

	void ActorInit(AActor* _NewActor);
	void LevelTick(float _DeltaTime);
	void LevelRender(float _DeltaTime);
	void LevelRelease(float _DeltaTime);
};