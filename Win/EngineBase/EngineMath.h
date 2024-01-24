#pragma once

struct float4
{
public:
	float X;
	float Y;
	float Z;
	float W;

public:
	float hX()
	{
		return X * 0.5f;
	}

	float hY()
	{
		return Y * 0.5f;
	}

	int ihX()
	{
		return static_cast<int>(hX());
	}

	int ihY()
	{
		return static_cast<int>(hY());
	}
};

using FVector = float4;

class EngineMath
{
public:
	EngineMath();
	~EngineMath();

	EngineMath(const EngineMath& _Other) = delete;
	EngineMath(EngineMath&& _Other) noexcept = delete;
	EngineMath& operator=(const EngineMath& _Other) = delete;
	EngineMath& operator=(EngineMath&& _Other) noexcept = delete;

protected:

private:

};