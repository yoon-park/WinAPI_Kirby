#include "PlayLevel.h"

#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include <EngineCore\EngineResourcesManager.h>
#include "Player.h"

UPlayLevel::UPlayLevel()
{

}

UPlayLevel::~UPlayLevel()
{

}

void UPlayLevel::BeginPlay()
{
	ULevel::BeginPlay();

	UEngineDirectory NewPath;

	NewPath.MoveParent();
	NewPath.Move("Resources");
	NewPath.Move("PlayLevel");

	std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);
	
	for (UEngineFile& File : AllFileList)
	{
		std::string FullPath = File.GetFullPath();
		UEngineResourcesManager::GetInst().LoadImg(FullPath);
	}

	Player* Kirby = SpawnActor<Player>();
}