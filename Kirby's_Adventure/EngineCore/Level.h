#pragma once
#include <map>
#include <list>

#include <EngineBase/EngineMath.h>
#include <EngineBase/NameObject.h>

class AActor;
class UEngineCore;
class UImageRenderer;

class ULevel : public UNameObject
{
	friend UEngineCore;
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

	virtual void LevelStart(ULevel* _PrevLevel)
	{
	
	};

	virtual void LevelEnd(ULevel* _NextLevel)
	{
	
	};

	template<typename ActorType>
	ActorType* SpawnActor(int _Order = 0)
	{
		ActorType* NewActor = new ActorType();
		ActorInit(NewActor);
		AllActor[_Order].push_back(NewActor);
		return NewActor;
	}

	FVector GetCameraPos() const
	{
		return CameraPos;
	}

	void SetCameraPos(FVector _CameraPos)
	{
		CameraPos = _CameraPos;
	}

	void AddCameraPos(FVector _CameraPos)
	{
		CameraPos += _CameraPos;
	}

protected:

private:
	FVector CameraPos = FVector::Zero;

	std::map<int, std::list<AActor*>> AllActor;
	std::map<int, std::list<UImageRenderer*>> Renderers;

	void ActorInit(AActor* _NewActor);
	void LevelTick(float _DeltaTime);
	void LevelRender(float _DeltaTime);
	void LevelRelease(float _DeltaTime);
};