#pragma once
#include "EngineMath.h"

enum ECollisionType
{
	Point,
	CirCle,
	Rect,
};

class FTransform
{
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

	bool Collision(ECollisionType _ThisType, ECollisionType _OtherType, const FTransform& _Other);

protected:

private:
	FVector Position;
	FVector Scale;
};