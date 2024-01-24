#pragma once
#include <map>

#include <EngineBase\EngineDebug.h>
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

	// ���� â (������ �����Ѵ�)
	EngineWindow MainWindow;

	void CoreInit(HINSTANCE _Init);

	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);
	virtual void End();

	template<typename LevelType>
	void CreateLevel(std::string_view _Name)
	{
		std::string UpperName = EngineString::ToUpper(_Name);

		if (AllLevel.contains(UpperName) == true)
		{
			MsgBoxAssert(std::string(_Name) + " : ���� �̸��� Level�� �̹� �����մϴ�.");
		}

		LevelType* NewLevel = new LevelType();
		LevelInit(NewLevel);
		AllLevel.insert(std::pair<std::string, ULevel*>(UpperName, NewLevel));
	}

	void ChangeLevel(std::string_view _Name);

	static void EngineStart(HINSTANCE _hInstance, EngineCore* _UserCore);

protected:
	EngineCore();

private:
	bool EngineInit = false;
	ULevel* CurLevel = nullptr;
	std::map<std::string, ULevel*> AllLevel;

	void LevelInit(ULevel* _Level);

	static void EngineTick();
	static void EngineEnd();
};

// ���� �ھ� (��ΰ� �� �� �ֵ��� ����)
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