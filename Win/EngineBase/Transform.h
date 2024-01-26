#pragma once
#include "EngineMath.h"

class FTransform
{
public:
	FTransform();
	~FTransform();

	FVector GetPosition()
	{
		return Position;
	}

	FVector GetScale()
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

	float Left()
	{
		return Position.X - Scale.hX();
	}

	float Right()
	{
		return Position.X + Scale.hX();
	}

	float Top()
	{
		return Position.Y - Scale.hY();
	}

	float Bottom()
	{
		return Position.Y + Scale.hY();
	}

	int iLeft()
	{
		return static_cast<int>(Left());
	}

	int iRight()
	{
		return static_cast<int>(Right());
	}

	int iTop()
	{
		return static_cast<int>(Top());
	}

	int iBottom()
	{
		return static_cast<int>(Bottom());
	}

protected:

private:
	FVector Position;
	FVector Scale;
};