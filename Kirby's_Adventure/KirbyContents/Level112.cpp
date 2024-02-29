#include "Level112.h"

#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include <EngineCore\EngineResourcesManager.h>
#include <EnginePlatform/EngineInput.h>
#include "BackGroundMap.h"
#include "HUD.h"
#include "Player.h"
#include "Monster.h"
#include "FadeOut.h"
#include "Level113.h"

ULevel112::ULevel112()
{

}

ULevel112::~ULevel112()
{

}

void ULevel112::BeginPlay()
{
	ULevel::BeginPlay();

	GEngine->CreateLevel<ULevel113>("Level113");
}

void ULevel112::Tick(float _DeltaTime)
{

}

void ULevel112::LevelStart(ULevel* _Level)
{
	ABackGroundMap* Map = SpawnActor<ABackGroundMap>();
	Map->SetMapImage("Stage1-2.png");
	Map->SetColMapImage("Stage1-2_Col.png");

	AHUD* HUD = SpawnActor<AHUD>();

	APlayer* Kirby = SpawnActor<APlayer>();
	Kirby->SetName("Kirby");
	Kirby->SetActorLocation({ 200, 200 });

	Fade = SpawnActor<AFadeOut>();
	Fade->SetActorLocation({ 400, 375 });
	Fade->SetActive(true, 0.5f);
	Fade->FadeStart(FadeOption::FadeIn);
}

void ULevel112::LevelEnd(ULevel* _Level)
{
	Fade->FadeStart(FadeOption::FadeOut);

	GEngine->DestroyLevel("Level112");
}