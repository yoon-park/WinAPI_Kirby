#pragma once
#include <map>

#include <EngineBase\EngineDebug.h>
#include <EngineBase\EngineTime.h>
#include <EngineBase\EngineString.h>
#include <EnginePlatform\EngineWindow.h>

class ULevel;

class UEngineCore
{
public:
	~UEngineCore();

	UEngineCore(const UEngineCore& _Other) = delete;
	UEngineCore(UEngineCore&& _Other) noexcept = delete;
	UEngineCore& operator=(const UEngineCore& _Other) = delete;
	UEngineCore& operator=(UEngineCore&& _Other) noexcept = delete;

	// 메인 창, 메인 타이머 (무조건 존재한다)
	UEngineWindow MainWindow;
	EngineTime MainTimer;

	void SetFrame(int _Frame)
	{
		Frame = _Frame;
		FrameTime = 1 / static_cast<float>(Frame);
	}

	void CoreInit(HINSTANCE _Init);
	void EngineStart(HINSTANCE _hInstance);

	template<typename LevelType>
	void CreateLevel(std::string_view _Name)
	{
		std::string UpperName = UEngineString::ToUpper(_Name);

		if (AllLevel.contains(UpperName) == true)
		{
			MsgBoxAssert(std::string(_Name) + " : 같은 이름의 Level이 이미 존재합니다.");
		}

		LevelType* NewLevel = new LevelType();
		LevelInit(NewLevel, _Name);
		AllLevel.insert(std::pair<std::string, ULevel*>(UpperName, NewLevel));
	}

	void ChangeLevel(std::string_view _Name);

	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);
	virtual void End();

protected:
	UEngineCore();

private:
	bool EngineInit = false;
	int Frame = -1;
	float FrameTime = 0.0f;
	float CurFrameTime = 0.0f;
	ULevel* CurLevel = nullptr;
	ULevel* NextLevel = nullptr;
	std::map<std::string, ULevel*> AllLevel;

	void CoreTick();
	void LevelInit(ULevel* _Level, std::string_view _Name);

	static void EngineTick();
	static void EngineEnd();
};

// 엔진 코어 (모두가 알 수 있도록 전역)
extern UEngineCore* GEngine;

#define ENGINESTART(USERCORE) \
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, \
	_In_opt_ HINSTANCE hPrevInstance, \
	_In_ LPWSTR    lpCmdLine, \
	_In_ int       nCmdShow) \
{ \
	LeakCheck; \
	USERCORE NewUserCore = USERCORE(); \
	NewUserCore.EngineStart(hInstance); \
}