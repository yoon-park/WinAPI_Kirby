#include "Stage113.h"

#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include <EngineCore\EngineResourcesManager.h>
#include "BackGroundMap.h"
#include "HUD.h"
#include "Player.h"
#include "Monster.h"
#include "FadeOut.h"

UStage113::UStage113()
{

}

UStage113::~UStage113()
{

}

void UStage113::BeginPlay()
{
	ULevel::BeginPlay();
}

void UStage113::Tick(float _DeltaTime)
{

}

void UStage113::LevelStart(ULevel* _Level)
{
	{
		ABackGroundMap* Map = SpawnActor<ABackGroundMap>();
		Map->SetMapImage("Stage1-3.png");
		Map->SetColMapImage("Stage1-3_Col.png");

		AHUD* HUD = SpawnActor<AHUD>();

		Fade = SpawnActor<AFadeOut>();
		Fade->SetActorLocation({ 400, 375 });
	}
}

void UStage113::LevelEnd(ULevel* _Level)
{

}