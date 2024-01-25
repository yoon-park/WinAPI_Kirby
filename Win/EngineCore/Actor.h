#pragma once
#include <EngineBase\FTransform.h>
#include "NameObject.h"
#include "TickObject.h"
#include "Level.h"

class ULevel;

class AActor : public UNameObject, public UTickObject
{
	friend ULevel;

public:
	AActor();
	~AActor();

	AActor(const AActor& _Other) = delete;
	AActor(AActor&& _Other) noexcept = delete;
	AActor& operator=(const AActor& _Other) = delete;
	AActor& operator=(AActor&& _Other) noexcept = delete;

	ULevel* GetWorld()
	{
		return World;
	}

	FTransform GetTransform()
	{
		return Transform;
	}

	FVector GetActorLocation()
	{
		return Transform.GetPosition();
	}

	void SetActorScale(FVector _Value)
	{
		Transform.SetScale(_Value);
	}

	void SetActorLocation(FVector _Value)
	{
		Transform.SetPosition(_Value);
	}

	void AddActorLocation(FVector _Value)
	{
		Transform.AddPosition(_Value);
	}

protected:

private:
	ULevel* World;
	FTransform Transform;

	void SetWorld(ULevel* _Value)
	{
		World = _Value;
	}
};