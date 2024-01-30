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
	UEngineDirectory NewPath;
	NewPath.MoveParent();

	NewPath.Move("ContentsResources");

	std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);
	UEngineResourcesManager::GetInst().LoadImg("C:\\GM\\Win\\ContentsResources\\AAAA.png");

	SpawnActor<Player>();

	// TODO
}