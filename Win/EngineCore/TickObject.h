#pragma once

class UTickObject
{
public:
	UTickObject();
	virtual ~UTickObject();

	UTickObject(const UTickObject& _Other) = delete;
	UTickObject(UTickObject&& _Other) noexcept = delete;
	UTickObject& operator=(const UTickObject& _Other) = delete;
	UTickObject& operator=(UTickObject&& _Other) noexcept = delete;

	bool IsOn()
	{
		return (IsUpdateValue) && (IsDeathValue == false);
	}

	bool IsDeath()
	{
		return IsDeathValue;
	}

	void On()
	{
		IsUpdateValue = true;
	}

	void Off()
	{
		IsUpdateValue = false;
	}

	void Death()
	{
		IsDeathValue = true;
	}

	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);

protected:

private:
	bool IsUpdateValue = true;
	bool IsDeathValue = false;
};