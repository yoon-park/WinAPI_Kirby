#include "Level112.h"

#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore\EngineResourcesManager.h>
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
	SetNextLevel("Level113");
}

void ULevel112::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (UEngineInput::IsDown(VK_ESCAPE) == true)
	{
		GEngine->MainWindow.Off();
	}

	FVector Pos = GetCameraPos();

	if (Pos.X <= 0.0f)
	{
		Pos.X = 0.0f;
	}

	if (Pos.Y <= 0.0f)
	{
		Pos.Y = 0.0f;
	}

	FVector ImageScale = Map->GetImageScale();

	if (Pos.X >= ImageScale.X - GEngine->MainWindow.GetWindowScale().X)
	{
		Pos.X = ImageScale.X - GEngine->MainWindow.GetWindowScale().X;
	}

	SetCameraPos(Pos);
}

void ULevel112::LevelStart(ULevel* _Level)
{
	Map = SpawnActor<ABackGroundMap>();
	Map->SetMapImage("Stage1-2.png");
	Map->SetColMapImage("Stage1-2_Col.png");

	Fade = SpawnActor<AFadeOut>();
	Fade->SetActorLocation({ 400, 375 });
	Fade->SetActive(true, 0.5f);
	Fade->FadeStart(FadeOption::FadeIn);

	AHUD* HUD = SpawnActor<AHUD>();

	APlayer* Kirby = SpawnActor<APlayer>();
	Kirby->SetName("Kirby");
	Kirby->SetActorType(EActorType::Player);
	Kirby->SetActorLocation({ 200, 200 });
}

void ULevel112::LevelEnd(ULevel* _Level)
{
	Fade->FadeStart(FadeOption::FadeOut);

	GEngine->DestroyLevel("Level112");
}