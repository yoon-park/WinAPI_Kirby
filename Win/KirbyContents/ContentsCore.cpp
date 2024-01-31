#include "ContentsCore.h"

#include "TitleLevel.h"
#include "PlayLevel.h"

ContentsCore::ContentsCore()
{

}

ContentsCore::~ContentsCore()
{

}

void ContentsCore::BeginPlay()
{
	MainWindow.SetWindowScale({ 800, 750 });
	SetFrame(60);

	UEngineCore::BeginPlay();

	CreateLevel<UTitleLevel>("TitleLevel");
	CreateLevel<UPlayLevel>("PlayLevel");

	ChangeLevel("PlayLevel");
}

void ContentsCore::Tick(float _DeltaTime)
{

}

void ContentsCore::End()
{

}