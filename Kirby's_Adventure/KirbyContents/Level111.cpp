#include "Level111.h"

#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include <EngineCore\EngineResourcesManager.h>
#include <EnginePlatform/EngineInput.h>
#include "BackGroundMap.h"
#include "HUD.h"
#include "Player.h"
#include "Monster.h"
#include "FadeOut.h"
#include "Level112.h"

ULevel111::ULevel111()
{

}

ULevel111::~ULevel111()
{

}

void ULevel111::BeginPlay()
{
	ULevel::BeginPlay();

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

		UEngineResourcesManager::GetInst().CuttingImage("Kirby_Right.png", 8, 8);
		UEngineResourcesManager::GetInst().CuttingImage("Kirby_Left.png", 8, 8);
	}

	GEngine->CreateLevel<ULevel112>("Level112");
}

void ULevel111::Tick(float _DeltaTime)
{

}

void ULevel111::LevelStart(ULevel* _Level)
{
	ABackGroundMap* Map = SpawnActor<ABackGroundMap>();
	Map->SetMapImage("Stage1-1.png");
	Map->SetColMapImage("Stage1-1_Col.png");

	AHUD* HUD = SpawnActor<AHUD>();

	APlayer* Kirby = SpawnActor<APlayer>();
	Kirby->SetName("Kirby");
	Kirby->SetActorLocation({ 200, 200 });

	AMonster* Monster = SpawnActor<AMonster>();
	Monster->SetName("Monster");
	Monster->SetActorLocation({ 500, 200 });

	Fade = SpawnActor<AFadeOut>();
	Fade->SetActorLocation({ 400, 375 });
	Fade->SetActive(true, 0.5f);
	Fade->FadeStart(FadeOption::FadeIn);
}

void ULevel111::LevelEnd(ULevel* _Level)
{
	Fade->FadeStart(FadeOption::FadeOut);
	
	GEngine->DestroyLevel("Level111");
}