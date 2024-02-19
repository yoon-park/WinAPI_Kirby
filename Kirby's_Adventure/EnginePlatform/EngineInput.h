#pragma once
#include <Windows.h>
#include <map>

#include <EngineBase\EngineDebug.h>

class UEngineInput
{
	friend class InputInitCreator;

private:
	class EngineKey
	{
		friend UEngineInput;

	public:
		EngineKey()
		{

		}

		EngineKey(int _Key)
			: Key(_Key)
		{

		}

		int Key = -1;

		float UpTime = 0.0f;
		float PressTime = 0.0f;
		bool Down = false;	
		bool Press = false; 
		bool Up = false;	
		bool Free = true;

		void KeyCheck(float _DeltaTime);
	};

public:
	UEngineInput();
	~UEngineInput();

	UEngineInput(const UEngineInput& _Other) = delete;
	UEngineInput(UEngineInput&& _Other) noexcept = delete;
	UEngineInput& operator=(const UEngineInput& _Other) = delete;
	UEngineInput& operator=(UEngineInput&& _Other) noexcept = delete;

	static float GetPressTime(int _Key)
	{
		if (AllKeys.contains(_Key) == false)
		{
			MsgBoxAssert("입력설정이 존재하지 않는 키 입니다");
		}

		return AllKeys[_Key].PressTime;
	}

	static bool IsDoubleClick(int _Key, float _ClickTime)
	{
		if (AllKeys.contains(_Key) == false)
		{
			MsgBoxAssert("입력설정이 존재하지 않는 키 입니다");
		}

		bool Value = AllKeys[_Key].Down;
		float Time = AllKeys[_Key].UpTime;

		if (AllKeys[_Key].Down && AllKeys[_Key].UpTime < _ClickTime == true)
		{
			return true;
		}

		return false;
	}

	static bool IsDown(int _Key)
	{
		if (AllKeys.contains(_Key) == false)
		{
			MsgBoxAssert("입력 설정이 존재하지 않는 키입니다.");
		}

		return AllKeys[_Key].Down;
	}

	static bool IsPress(int _Key)
	{
		if (AllKeys.contains(_Key) == false)
		{
			MsgBoxAssert("입력 설정이 존재하지 않는 키입니다");
		}

		return AllKeys[_Key].Press;
	}

	static bool IsUp(int _Key)
	{
		if (AllKeys.contains(_Key) == false)
		{
			MsgBoxAssert("입력 설정이 존재하지 않는 키입니다");
		}

		return AllKeys[_Key].Up;
	}

	static bool IsFree(int _Key)
	{
		if (AllKeys.contains(_Key) == false)
		{
			MsgBoxAssert("입력 설정이 존재하지 않는 키입니다");
		}

		return AllKeys[_Key].Free;
	}

	static bool IsAnykeyDown()
	{
		return AnykeyDown;
	}

	static bool IsAnykeyPress()
	{
		return AnykeyPress;
	}

	static bool IsAnykeyUp()
	{
		return AnykeyUp;
	}

	static bool IsAnykeyFree()
	{
		return AnykeyFree;
	}

	static void KeyCheckTick(float _DeltaTime);

protected:
	static bool AnykeyDown;
	static bool AnykeyPress;
	static bool AnykeyUp;
	static bool AnykeyFree;

	static std::map<int, EngineKey> AllKeys;

private:
	static void InputInit();
};