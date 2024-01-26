#pragma once
#include <EngineBase\Transform.h>
#include "NameObject.h"
#include "TickObject.h"
#include "Level.h"
#include "ImageRenderer.h"

class ULevel;
class UActorComponent;
class UImageRenderer;

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

	void SetActorLocation(FVector _Value)
	{
		Transform.SetPosition(_Value);
	}

	void AddActorLocation(FVector _Value)
	{
		Transform.AddPosition(_Value);
	}

	void SetActorScale(FVector _Value)
	{
		Transform.SetScale(_Value);
	}

	UImageRenderer* CreateImageRenderer(int Order = 0);

protected:

private:
	ULevel* World = nullptr;
	FTransform Transform = FTransform();

	std::list<UImageRenderer*> Renderers;

	void SetWorld(ULevel* _Value)
	{
		World = _Value;
	}
};