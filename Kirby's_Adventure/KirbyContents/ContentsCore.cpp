#include "ContentsCore.h"

#include <EnginePlatform\EngineInput.h>
#include "TitleLevel.h"
#include "PlayLevel.h"

UContentsCore::UContentsCore()
{

}

UContentsCore::~UContentsCore()
{

}

void UContentsCore::BeginPlay()
{
	MainWindow.SetWindowScale({ 800, 700 });
	MainWindow.SetWindowPosition({ 0, 0 });

	UEngineCore::BeginPlay();

	CreateLevel<UTitleLevel>("TitleLevel");
	CreateLevel<UPlayLevel>("PlayLevel");

	ChangeLevel("PlayLevel");
}

void UContentsCore::Tick(float _DeltaTime)
{
	UEngineCore::Tick(_DeltaTime);

	if (UEngineInput::IsDown(VK_F2) == true)
	{
		GEngine->EngineDebugSwitch();
	}
}

void UContentsCore::End()
{

}