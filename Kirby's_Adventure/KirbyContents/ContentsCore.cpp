#include "ContentsCore.h"

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

}

void UContentsCore::End()
{

}