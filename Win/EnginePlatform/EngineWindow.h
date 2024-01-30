#pragma once
#include <Windows.h>
#include <string>

class UWindowImage;

class UEngineWindow
{
public:
	UEngineWindow();
	~UEngineWindow();

	UEngineWindow(const UEngineWindow& _Other) = delete;
	UEngineWindow(UEngineWindow&& _Other) noexcept = delete;
	UEngineWindow& operator=(const UEngineWindow& _Other) = delete;
	UEngineWindow& operator=(UEngineWindow&& _Other) noexcept = delete;

	UWindowImage* GetWindowImage()
	{
		return WindowImage;
	}

	void Open(std::string_view _Title = "Title");

	static void Init(HINSTANCE _hInst);
	static unsigned __int64 WindowMessageLoop(void(*_Update)(), void(*_End)());

protected:

private:
	HWND hWnd = nullptr;
	UWindowImage* WindowImage = nullptr;

	static bool WindowLive;
	static HINSTANCE hInstance;

	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
};