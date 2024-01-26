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
	SetFrame(60);

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