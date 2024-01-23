#pragma once
#include <EnginePlatform\EngineWindow.h>

class EngineCore
{
public:
	EngineCore();
	~EngineCore();

	EngineCore(const EngineCore& _Other) = delete;
	EngineCore(EngineCore&& _Other) noexcept = delete;
	EngineCore& operator=(const EngineCore& _Other) = delete;
	EngineCore& operator=(EngineCore&& _Other) noexcept = delete;

	// 메인 창 (무조건 존재한다)
	EngineWindow MainWindow;

	void CoreInit(HINSTANCE _Init);

	virtual void EngineStart();
	virtual void EngineUpdate();
	virtual void EngineEnd();

protected:

private:
	bool EngineInit = false;
};

// 진입점 (사용자로부터 숨겨져 있다)
#define ENGINESTART(USERCORE) \
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, \
	_In_opt_ HINSTANCE hPrevInstance, \
	_In_ LPWSTR    lpCmdLine, \
	_In_ int       nCmdShow) \
{ \
	USERCORE NewUserCore; \
	EngineCore* Ptr = &NewUserCore; \
	Ptr->CoreInit(hInstance); \
	Ptr->EngineStart(); \
	EngineWindow::WindowMessageLoop(); \
}