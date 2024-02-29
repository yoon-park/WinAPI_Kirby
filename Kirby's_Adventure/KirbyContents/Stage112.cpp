#include "Stage112.h"

#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include <EngineCore\EngineResourcesManager.h>
#include <EnginePlatform/EngineInput.h>
#include "BackGroundMap.h"
#include "HUD.h"
#include "Player.h"
#include "Monster.h"
#include "FadeOut.h"

UStage112::UStage112()
{

}

UStage112::~UStage112()
{

}

void UStage112::BeginPlay()
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

	{
		ABackGroundMap* Map = SpawnActor<ABackGroundMap>();
		Map->SetMapImage("Stage1-2.png");
		Map->SetColMapImage("Stage1-2_Col.png");

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
}

void UStage112::Tick(float _DeltaTime)
{

}

void UStage112::LevelStart(ULevel* _Level)
{

}

void UStage112::LevelEnd(ULevel* _Level)
{
	Fade->FadeStart(FadeOption::FadeOut);
}