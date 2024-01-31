#pragma once
#include <Windows.h>
#include <string>

#include <EngineBase\EngineMath.h>

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

	UWindowImage* GetBackBufferImage()
	{
		return BackBufferImage;
	}

	void SetWindowPosition(const FVector& _Pos);
	void SetWindowScale(const FVector& _Scale);

	void Open(std::string_view _Title = "Title");
	void ScreenClear();
	void ScreenUpdate();

	static void Init(HINSTANCE _hInst);
	static unsigned __int64 WindowMessageLoop(void(*_Update)(), void(*_End)());

protected:

private:
	FVector Scale;
	HWND hWnd = nullptr;
	UWindowImage* WindowImage = nullptr;
	UWindowImage* BackBufferImage = nullptr;

	static bool WindowLive;
	static HINSTANCE hInstance;

	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
};