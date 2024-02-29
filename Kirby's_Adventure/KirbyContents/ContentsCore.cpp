#include "ContentsCore.h"

#include <EnginePlatform\EngineInput.h>
#include "TitleLevel.h"
#include "Stage112.h"
#include "Stage113.h"

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
	CreateLevel<UStage112>("Stage112");
	CreateLevel<UStage113>("Stage113");

	ChangeLevel("Stage112");
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