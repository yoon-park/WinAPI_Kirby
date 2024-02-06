#pragma once
#include <Windows.h>
#include <map>

#include <EngineBase\EngineDebug.h>

class EngineInput
{
	friend class InputInitCreator;

private:
	class EngineKey
	{
		friend EngineInput;

	public:
		EngineKey()
		{

		}

		EngineKey(int _Key)
			: Key(_Key)
		{

		}

		int Key = -1;

		bool Down = false;	
		bool Press = false; 
		bool Up = false;	
		bool Free = true;	

		float PressTime = 0.0f;

		void KeyCheck();
	};

public:
	EngineInput();
	~EngineInput();

	EngineInput(const EngineInput& _Other) = delete;
	EngineInput(EngineInput&& _Other) noexcept = delete;
	EngineInput& operator=(const EngineInput& _Other) = delete;
	EngineInput& operator=(EngineInput&& _Other) noexcept = delete;

	static bool IsDown(int _Key)
	{
		if (AllKeys.contains(_Key) == false)
		{
			MsgBoxAssert("�Է� ������ �������� �ʴ� Ű�Դϴ�.");
		}

		return AllKeys[_Key].Down;
	}

	static bool IsPress(int _Key)
	{
		if (AllKeys.contains(_Key) == false)
		{
			MsgBoxAssert("�Է� ������ �������� �ʴ� Ű�Դϴ�");
		}

		return AllKeys[_Key].Press;
	}

	static bool IsUp(int _Key)
	{
		if (AllKeys.contains(_Key) == false)
		{
			MsgBoxAssert("�Է� ������ �������� �ʴ� Ű�Դϴ�");
		}

		return AllKeys[_Key].Up;
	}

	static bool IsFree(int _Key)
	{
		if (AllKeys.contains(_Key) == false)
		{
			MsgBoxAssert("�Է� ������ �������� �ʴ� Ű�Դϴ�");
		}

		return AllKeys[_Key].Free;
	}

	static void KeyCheckTick(float _DeltaTime);

protected:
	static std::map<int, EngineKey> AllKeys;

private:
	static void InputInit();
};