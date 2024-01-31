#include "TitleLevel.h"

#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
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

void UTitleLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}