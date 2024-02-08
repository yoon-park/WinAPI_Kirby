#include "PlayLevel.h"

#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include <EngineCore\EngineResourcesManager.h>
#include "BackGroundMap.h"
#include "HUD.h"
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
}

void UPlayLevel::Tick(float _DeltaTime)
{

}

void UPlayLevel::LevelStart(ULevel* _Level)
{
	UEngineDirectory NewPath;

	NewPath.MoveParent();
	NewPath.Move("Resources");
	NewPath.Move("Common");

	std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);
	for (UEngineFile& File : AllFileList)
	{
		UEngineResourcesManager::GetInst().LoadImg(File.GetFullPath());
	}

	NewPath.MoveParent();
	NewPath.Move("PlayLevel");
	
	AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);
	for (UEngineFile& File : AllFileList)
	{
		UEngineResourcesManager::GetInst().LoadImg(File.GetFullPath());
	}

	UEngineResourcesManager::GetInst().CuttingImage("Kirby_Right.png", 5, 3);
	UEngineResourcesManager::GetInst().CuttingImage("Kirby_Left.png", 5, 3);

	ABackGroundMap* Map = SpawnActor<ABackGroundMap>();
	AHUD* HUD = SpawnActor<AHUD>();
	APlayer* Kirby = SpawnActor<APlayer>();
	Kirby->SetActorLocation({ 200, 200 });
}

void UPlayLevel::LevelEnd(ULevel* _Level)
{

}