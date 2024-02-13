#pragma once
#include <EngineBase\EngineDebug.h>

class UTickObject
{
public:
	UTickObject();
	virtual ~UTickObject();

	UTickObject(const UTickObject& _Other) = delete;
	UTickObject(UTickObject&& _Other) noexcept = delete;
	UTickObject& operator=(const UTickObject& _Other) = delete;
	UTickObject& operator=(UTickObject&& _Other) noexcept = delete;

	int GetOrder() const
	{
		return Order;
	}

	virtual void SetOrder(int _Order)
	{
		Order = _Order;
	}

	bool IsActive()
	{
		return IsActiveValue && (IsDestroyValue == false);
	}

	void SetActive(bool _Active, float _ActiveTime = 0.0f)
	{
		ActiveTime = _ActiveTime;

		if (_Active == true && ActiveTime == 0.0f)
		{
			IsActiveValue = _Active;
			return;
		}

		if (_Active == true && ActiveTime != 0.0f)
		{
			IsActiveUpdate = true;
		}

		IsActiveValue = false;
	}

	void ActiveOn()
	{
		IsActiveValue = true;
	}

	void ActiveOff()
	{
		IsActiveValue = false;
	}

	virtual void ActiveUpdate(float _DeltaTime)
	{
		ActiveTime -= _DeltaTime;

		if (IsActiveUpdate == true)
		{
			if (ActiveTime <= 0.0f)
			{
				IsActiveUpdate = false;
				IsActiveValue = true;
				return;
			}
		}
	}

	bool IsDestroy() const
	{
		return IsDestroyValue;
	}

	virtual void Destroy(float _DestroyTime = 0.0f)
	{
		IsDestroyUpdate = true;
		DestroyTime = _DestroyTime;
		if (_DestroyTime <= 0.0f)
		{
			IsDestroyValue = true;
		}
	}

	virtual void DestroyUpdate(float _DeltaTime)
	{
		if (IsDestroyUpdate == false)
		{
			return;
		}

		DestroyTime -= _DeltaTime;
		if (DestroyTime <= 0.0f)
		{
			Destroy(0.0f);
		}
	}

	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);

protected:

private:
	int Order = 0;

	bool IsActiveUpdate = false;
	float ActiveTime = 0.0f;
	bool IsActiveValue = true;

	bool IsDestroyUpdate = false;
	float DestroyTime = 0.0f;
	bool IsDestroyValue = false;
};