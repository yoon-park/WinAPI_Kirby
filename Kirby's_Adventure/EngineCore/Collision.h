#pragma once
#include <vector>

#include "SceneComponent.h"

class UCollision : public USceneComponent
{
public:
	UCollision();
	~UCollision();

	UCollision(const UCollision& _Other) = delete;
	UCollision(UCollision&& _Other) noexcept = delete;
	UCollision& operator=(const UCollision& _Other) = delete;
	UCollision& operator=(UCollision&& _Other) noexcept = delete;

	void SetOrder(int _Order) override;

	void SetColType(ECollisionType _Type)
	{
		ColType = _Type;
	}

	template<typename EnumType>
	bool CollisionCheck(EnumType _Order, std::vector<UCollision*>& _Result)
	{
		return CollisionCheck(static_cast<int>(_Order), _Result);
	}

	bool CollisionCheck(int _Order, std::vector<UCollision*>& _Result);

	void DebugRender(FVector _CameraPos);

protected:
	void BeginPlay() override;

private:
	ECollisionType ColType = ECollisionType::Rect;
};