#include "Level113.h"

#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include <EngineCore\EngineResourcesManager.h>
#include "BackGroundMap.h"
#include "HUD.h"
#include "Player.h"
#include "Monster.h"
#include "FadeOut.h"

ULevel113::ULevel113()
{

}

ULevel113::~ULevel113()
{

}

void ULevel113::BeginPlay()
{
	ULevel::BeginPlay();
}

void ULevel113::Tick(float _DeltaTime)
{

}

void ULevel113::LevelStart(ULevel* _Level)
{
	{
		ABackGroundMap* Map = SpawnActor<ABackGroundMap>();
		Map->SetMapImage("Stage1-3.png");
		Map->SetColMapImage("Stage1-3_Col.png");

		AHUD* HUD = SpawnActor<AHUD>();

		APlayer* Kirby = SpawnActor<APlayer>();
		Kirby->SetName("Kirby");
		Kirby->SetActorLocation({ 200, 200 });

		Fade = SpawnActor<AFadeOut>();
		Fade->SetActorLocation({ 400, 375 });
		Fade->SetActive(true, 0.5f);
		Fade->FadeStart(FadeOption::FadeIn);
	}
}

void ULevel113::LevelEnd(ULevel* _Level)
{
	Fade->FadeStart(FadeOption::FadeOut);

	GEngine->DestroyLevel("Level113");
}