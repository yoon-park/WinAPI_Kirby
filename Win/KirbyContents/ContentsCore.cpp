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
	SetFrame(60);

	UEngineCore::BeginPlay();

	CreateLevel<UTitleLevel>("TitleLevel");
	CreateLevel<UPlayLevel>("PlayLevel");

	ChangeLevel("TitleLevel");
}

void UContentsCore::Tick(float _DeltaTime)
{

}

void UContentsCore::End()
{

}