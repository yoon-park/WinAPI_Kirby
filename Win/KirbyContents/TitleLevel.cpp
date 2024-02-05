#include "TitleLevel.h"

#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include <EnginePlatform\EngineInput.h>
#include <EngineCore\EngineCore.h>
#include <EngineCore\EngineResourcesManager.h>
#include "TitleLogo.h"

UTitleLevel::UTitleLevel()
{

}

UTitleLevel::~UTitleLevel()
{

}

void UTitleLevel::BeginPlay()
{
	ULevel::BeginPlay();
}

void UTitleLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (EngineInput::IsDown('P'))
	{
		GEngine->ChangeLevel("PlayLevel");
	}
}

void UTitleLevel::LevelStart(ULevel* _Level)
{
	UEngineDirectory NewPath;

	NewPath.MoveParent();
	NewPath.Move("Resources");
	NewPath.Move("TitleLevel");

	std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);

	for (UEngineFile& File : AllFileList)
	{
		std::string FullPath = File.GetFullPath();
		UEngineResourcesManager::GetInst().LoadImg(FullPath);
	}

	ATitleLogo* Logo = SpawnActor<ATitleLogo>();
}
void UTitleLevel::LevelEnd(ULevel* _Level)
{

}