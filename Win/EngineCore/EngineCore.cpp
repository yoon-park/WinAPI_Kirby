#include "EngineCore.h"

#include <Windows.h>

#include "EnginePlatform\EngineInput.h"
#include "Level.h"

UEngineCore* GEngine = nullptr;

void UEngineCore::EngineStart(HINSTANCE _hInstance, UEngineCore* _UserCore)
{
	UEngineCore* Ptr = _UserCore;
	GEngine = Ptr;

	Ptr->MainTimer.TimeCheckStart();
	Ptr->CoreInit(_hInstance);
	Ptr->BeginPlay();

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

void UEngineCore::BeginPlay()
{

}

void UEngineCore::Tick(float _DeltaTime)
{

}

void UEngineCore::End()
{

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

void UEngineCore::LevelInit(ULevel* _Level)
{
	_Level->BeginPlay();
}

void UEngineCore::ChangeLevel(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (AllLevel.contains(UpperName) == false)
	{
		MsgBoxAssert(std::string(_Name) + "라는 존재하지 않는 레벨로 이동하려 했습니다.");
	}

	CurLevel = AllLevel[UpperName];
}