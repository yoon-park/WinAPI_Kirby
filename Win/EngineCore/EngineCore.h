#pragma once
#include <map>

#include <EngineBase\EngineDebug.h>
#include <EngineBase\EngineTime.h>
#include <EngineBase\EngineString.h>
#include <EnginePlatform\EngineWindow.h>

class ULevel;

class EngineCore
{
public:
	~EngineCore();

	EngineCore(const EngineCore& _Other) = delete;
	EngineCore(EngineCore&& _Other) noexcept = delete;
	EngineCore& operator=(const EngineCore& _Other) = delete;
	EngineCore& operator=(EngineCore&& _Other) noexcept = delete;

	// 메인 창, 메인 타이머 (무조건 존재한다)
	UEngineWindow MainWindow;
	EngineTime MainTimer;

	void CoreInit(HINSTANCE _Init);

	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);
	virtual void End();

	template<typename LevelType>
	void CreateLevel(std::string_view _Name)
	{
		std::string UpperName = UEngineString::ToUpper(_Name);

		if (AllLevel.contains(UpperName) == true)
		{
			MsgBoxAssert(std::string(_Name) + " : 같은 이름의 Level이 이미 존재합니다.");
		}

		LevelType* NewLevel = new LevelType();
		LevelInit(NewLevel);
		AllLevel.insert(std::pair<std::string, ULevel*>(UpperName, NewLevel));
	}

	void ChangeLevel(std::string_view _Name);

	void SetFrame(int _Frame)
	{
		Frame = _Frame;
		FrameTime = 1 / static_cast<float>(Frame);
	}

	static void EngineStart(HINSTANCE _hInstance, EngineCore* _UserCore);

protected:
	EngineCore();

private:
	bool EngineInit = false;

	int Frame = -1;
	float FrameTime = 0.0f;
	float CurFrameTime = 0.0f;

	ULevel* CurLevel = nullptr;
	std::map<std::string, ULevel*> AllLevel;

	void CoreTick();
	void LevelInit(ULevel* _Level);

	static void EngineTick();
	static void EngineEnd();
};

// 엔진 코어 (모두가 알 수 있도록 전역)
extern EngineCore* GEngine;

#define ENGINESTART(USERCORE) \
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, \
	_In_opt_ HINSTANCE hPrevInstance, \
	_In_ LPWSTR    lpCmdLine, \
	_In_ int       nCmdShow) \
{ \
	LeakCheck; \
	USERCORE NewUserCore = USERCORE(); \
	EngineCore::EngineStart(hInstance, &NewUserCore); \
}