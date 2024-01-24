#pragma once
#include <Windows.h>
#include <string>

class EngineWindow
{
public:
	EngineWindow();
	~EngineWindow();

	EngineWindow(const EngineWindow& _Other) = delete;
	EngineWindow(EngineWindow&& _Other) noexcept = delete;
	EngineWindow& operator=(const EngineWindow& _Other) = delete;
	EngineWindow& operator=(EngineWindow&& _Other) noexcept = delete;

	HDC GetWindowDC()
	{
		return hDC;
	}

	void Open(std::string_view _Title = "Title");

	static void Init(HINSTANCE _hInst);
	static unsigned __int64 WindowMessageLoop(void(*_Update)(), void(*_End)());

protected:

private:
	HWND hWnd = nullptr;
	HDC hDC = nullptr;

	static bool WindowLive;
	static HINSTANCE hInstance;

	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
};