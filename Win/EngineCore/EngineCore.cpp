#include "EngineCore.h"

#include <Windows.h>

#include "Level.h"

EngineCore* GEngine = nullptr;

void EngineCore::EngineStart(HINSTANCE _hInstance, EngineCore* _UserCore)
{
	EngineCore* Ptr = _UserCore;
	GEngine = Ptr;
	Ptr->CoreInit(_hInstance);
	Ptr->BeginPlay();
	EngineWindow::WindowMessageLoop(EngineTick, EngineEnd);
}

void EngineCore::EngineTick()
{
	if (GEngine->CurLevel == nullptr)
	{
		MsgBoxAssert("������ ������ ������ �������� �ʾҽ��ϴ�.");
	}

	GEngine->CurLevel->Tick(0.0f);
	GEngine->CurLevel->ActorTick(0.0f);
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

	EngineWindow::Init(_HINSTANCE);
	MainWindow.Open();

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

void EngineCore::ChangeLevel(std::string_view _Name)
{
	std::string UpperName = EngineString::ToUpper(_Name);

	if (AllLevel.contains(UpperName) == false)
	{
		MsgBoxAssert(std::string(_Name) + "��� �������� �ʴ� ������ ü���� �Ϸ��� �߽��ϴ�");
	}

	CurLevel = AllLevel[UpperName];
}

void EngineCore::LevelInit(ULevel* _Level)
{
	_Level->BeginPlay();
}