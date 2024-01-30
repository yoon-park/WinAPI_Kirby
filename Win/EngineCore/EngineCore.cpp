#include "EngineCore.h"

#include <Windows.h>

#include "EnginePlatform\EngineInput.h"
#include "Level.h"

EngineCore* GEngine = nullptr;

void EngineCore::EngineStart(HINSTANCE _hInstance, EngineCore* _UserCore)
{
	EngineCore* Ptr = _UserCore;
	GEngine = Ptr;

	Ptr->MainTimer.TimeCheckStart();
	Ptr->CoreInit(_hInstance);
	Ptr->BeginPlay();

	UEngineWindow::WindowMessageLoop(EngineTick, EngineEnd);
}

void EngineCore::EngineTick()
{
	GEngine->CoreTick();
}

void EngineCore::EngineEnd()
{
	for (std::pair<const std::string, ULevel*>& _Pair : GEngine->AllLevel)
	{
		if (_Pair.second == nullptr)
		{
			continue;
		}

		delete _Pair.second;
		_Pair.second = nullptr;
	}

	GEngine->AllLevel.clear();
}

EngineCore::EngineCore()
{

}

EngineCore::~EngineCore()
{

}

void EngineCore::CoreInit(HINSTANCE _HINSTANCE)
{
	if (EngineInit == true)
	{
		return;
	}

	UEngineWindow::Init(_HINSTANCE);
	MainWindow.Open();

	this->AllLevel;

	EngineInit = true;
}

void EngineCore::BeginPlay()
{

}

void EngineCore::Tick(float _DeltaTime)
{

}

void EngineCore::End()
{

}

void EngineCore::CoreTick()
{
	float DeltaTime = MainTimer.TimeCheck();
	double dDeltaTime = MainTimer.GetDeltaTime();

	if (Frame >= 1)
	{
		CurFrameTime += DeltaTime;

		if (CurFrameTime <= FrameTime)
		{
			return;
		}

		CurFrameTime -= FrameTime;
		DeltaTime = FrameTime;
	}

	EngineInput::KeyCheckTick(DeltaTime);

	if (CurLevel == nullptr)
	{
		MsgBoxAssert("엔진을 시작할 레벨이 지정되지 않았습니다.");
	}

	CurLevel->Tick(DeltaTime);
	CurLevel->LevelTick(DeltaTime);
	CurLevel->LevelRender(DeltaTime);
	CurLevel->LevelRelease(DeltaTime);
}

void EngineCore::LevelInit(ULevel* _Level)
{
	_Level->BeginPlay();
}

void EngineCore::ChangeLevel(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (AllLevel.contains(UpperName) == false)
	{
		MsgBoxAssert(std::string(_Name) + "라는 존재하지 않는 레벨로 이동하려 했습니다.");
	}

	CurLevel = AllLevel[UpperName];
}