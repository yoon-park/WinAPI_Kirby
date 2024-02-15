#include "EngineCore.h"

#include <Windows.h>

#include "EnginePlatform\EngineInput.h"
#include "Level.h"

UEngineCore* GEngine = nullptr;
bool UEngineCore::IsDebugValue = false;

UEngineCore::UEngineCore()
{

}

UEngineCore::~UEngineCore()
{

}

void UEngineCore::CoreInit(HINSTANCE _HINSTANCE)
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

void UEngineCore::CoreTick()
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

	if (DeltaTime >= 1.0f / 60.0f)
	{
		DeltaTime = 1.0f / 60.0f;
	}

	UEngineInput::KeyCheckTick(DeltaTime);

	if (NextLevel != nullptr)
	{
		if (CurLevel != nullptr)
		{
			CurLevel->LevelEnd(NextLevel);
		}

		NextLevel->LevelStart(CurLevel);
		CurLevel = NextLevel;
		NextLevel = nullptr;
	}

	if (CurLevel == nullptr)
	{
		MsgBoxAssert("엔진을 시작할 레벨이 지정되지 않았습니다.");
	}

	GEngine->Tick(DeltaTime);
	CurLevel->Tick(DeltaTime);
	CurLevel->LevelTick(DeltaTime);
	MainWindow.ScreenClear();
	CurLevel->LevelRender(DeltaTime);
	MainWindow.ScreenUpdate();
	CurLevel->LevelRelease(DeltaTime);
}

void UEngineCore::EngineStart(HINSTANCE _hInstance)
{
	GEngine = this;
	MainTimer.TimeCheckStart();
	CoreInit(_hInstance);
	BeginPlay();

	UEngineWindow::WindowMessageLoop(EngineTick, EngineEnd);
}

void UEngineCore::EngineTick()
{
	GEngine->CoreTick();
}

void UEngineCore::EngineEnd()
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

void UEngineCore::LevelInit(ULevel* _Level, std::string_view _Name)
{
	_Level->SetName(_Name);
}

void UEngineCore::ChangeLevel(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (AllLevel.contains(UpperName) == false)
	{
		MsgBoxAssert(std::string(_Name) + "라는 존재하지 않는 레벨로 이동하려 했습니다.");
	}

	NextLevel = AllLevel[UpperName];
}

void UEngineCore::BeginPlay()
{

}

void UEngineCore::Tick(float _DeltaTime)
{

}

void UEngineCore::End()
{

}