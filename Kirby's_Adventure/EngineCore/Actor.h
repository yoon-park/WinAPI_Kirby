#pragma once
#include <EngineBase\Transform.h>
#include <EngineBase/NameObject.h>
#include "TickObject.h"
#include "Level.h"
#include "Collision.h"
#include "ImageRenderer.h"

class ULevel;
class UActorComponent;
class UCollision;
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

	template<typename EnumType>
	UCollision* CreateCollision(EnumType _Order = 0)
	{
		return CreateCollision(static_cast<int>(_Order));
	}

	UCollision* CreateCollision(int _Order = 0);

	template<typename EnumType>
	UImageRenderer* CreateImageRenderer(EnumType _Order = 0)
	{
		return CreateImageRenderer(static_cast<int>(_Order));
	}

	UImageRenderer* CreateImageRenderer(int _Order = 0);

	void AllRenderersActiveOff();
	void AllRenderersActiveOn();

	void ActiveUpdate(float _DeltaTime) override;
	void Destroy(float _DestroyTime = 0.0f) override;
	void DestroyUpdate(float _DeltaTime) override;
	void CheckReleaseChild();

protected:
	void Tick(float _DeltaTime) override;

private:
	ULevel* World = nullptr;
	FTransform Transform = FTransform();

	std::list<UCollision*> Collisions;
	std::list<UImageRenderer*> Renderers;

	void SetWorld(ULevel* _Value)
	{
		World = _Value;
	}
};