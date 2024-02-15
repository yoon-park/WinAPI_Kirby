#pragma once
#include "EngineMath.h"

enum ECollisionType
{
	Point,
	CirCle,
	Rect,
	Max
};

class CollisionFunctionInit;

class FTransform
{
	friend CollisionFunctionInit;

public:
	FTransform();
	FTransform(const FVector& _Pos, const FVector& _Scale)
		: Position(_Pos), Scale(_Scale)
	{

	}
	~FTransform();

	FVector GetPosition() const
	{
		return Position;
	}

	FVector GetScale() const
	{
		return Scale;
	}

	float GetRadius() const
	{
		return Scale.hX();
	}

	void SetPosition(FVector _Value)
	{
		Position = _Value;
	}

	void AddPosition(FVector _Value)
	{
		Position += _Value;
	}

	void SetScale(FVector _Value)
	{
		Scale = _Value;
	}

	void SetRadius(float _Radius)
	{
		Scale = float4::Zero;
		Scale.X = _Radius * 2.0f;
	}

	float Left() const
	{
		return Position.X - Scale.hX();
	}

	float Right() const
	{
		return Position.X + Scale.hX();
	}

	float Top() const
	{
		return Position.Y - Scale.hY();
	}

	float Bottom() const
	{
		return Position.Y + Scale.hY();
	}

	int iLeft() const
	{
		return std::lround(Left());
	}

	int iRight() const
	{
		return std::lround(Right());
	}

	int iTop() const
	{
		return std::lround(Top());
	}

	int iBottom() const
	{
		return std::lround(Bottom());
	}

	FVector LeftTop() const
	{
		return { Left(), Top() };
	}

	FVector RightTop() const
	{
		return { Right(), Top() };
	}

	FVector LeftBottom() const
	{
		return { Left(), Bottom() };
	}

	FVector RightBottom() const
	{
		return { Right(), Bottom() };
	}

	bool Collision(ECollisionType _ThisType, ECollisionType _OtherType, const FTransform& _Other);

	static bool CircleToCircle(const FTransform& _Left, const FTransform& _Right);
	static bool CircleToRect(const FTransform& _Left, const FTransform& _Right);
	static bool CircleToPoint(const FTransform& _Left, const FTransform& _Right);
	static bool RectToRect(const FTransform& _Left, const FTransform& _Right);
	static bool RectToCircle(const FTransform& _Left, const FTransform& _Right);
	static bool RectToPoint(const FTransform& _Left, const FTransform& _Right);
	static bool PointToRect(const FTransform& _Left, const FTransform& _Right);
	static bool PointToCircle(const FTransform& _Left, const FTransform& _Right);

protected:

private:
	FVector Position;
	FVector Scale;

	static bool (*CollisionFunction[static_cast<int>(ECollisionType::Max)][static_cast<int>(ECollisionType::Max)])(const FTransform& _Left, const FTransform& _Right);
};