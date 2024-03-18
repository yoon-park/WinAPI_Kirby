#include "Level111.h"

#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore\EngineResourcesManager.h>
#include "ContentsHelper.h"
#include "Level112.h"
#include "BackGroundMap.h"
#include "HUD.h"
#include "FadeOut.h"
#include "Player.h"
#include "WaddleDee.h"
#include "BrontoBurt.h"
#include "PoppyBrosJr.h"
#include "Sparky.h"
#include "HotHead.h"

ULevel111::ULevel111()
{

}

ULevel111::~ULevel111()
{

}

void ULevel111::BeginPlay()
{
	ULevel::BeginPlay();

	GEngine->CreateLevel<ULevel112>("Level112");
	SetNextLevel("Level112");
}

void ULevel111::Tick(float _DeltaTime)
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

void ULevel111::LevelStart(ULevel* _Level)
{
	Map = SpawnActor<ABackGroundMap>();
	Map->SetMapImage("Stage1-1.png");
	Map->SetColMapImage("Stage1-1_Col.png");

	Fade = SpawnActor<AFadeOut>();
	Fade->SetActorLocation({ 400, 375 });
	Fade->SetActive(true, 0.5f);
	Fade->FadeStart(FadeOption::FadeIn);

	AHUD* HUD = SpawnActor<AHUD>();
	HUD->SetHUDImage("HUDUI_Normal.png");

	APlayer* Kirby = SpawnActor<APlayer>();
	Kirby->SetName("Kirby");
	Kirby->SetActorType(EActorType::Player);
	Kirby->SetActorLocation({ 200, 200 });
	Kirby->SetActiveAbility(UContentsHelper::KirbyAbilityType);

	AWaddleDee* WaddleDee = SpawnActor<AWaddleDee>();
	WaddleDee->SetName("WaddleDee");
	WaddleDee->SetActorType(EActorType::Monster);
	WaddleDee->SetActorLocation({ 1500, 350 });

	ABrontoBurt* BrontoBurt = SpawnActor<ABrontoBurt>();
	BrontoBurt->SetName("BrontoBurt");
	BrontoBurt->SetActorType(EActorType::Monster);
	BrontoBurt->SetActorLocation({ 2000, 100 });

	APoppyBrosJr* PoppyBrosJr = SpawnActor<APoppyBrosJr>();
	PoppyBrosJr->SetName("PoppyBrosJr");
	PoppyBrosJr->SetActorType(EActorType::Monster);
	PoppyBrosJr->SetActorLocation({ 400, 350 });

	AHotHead* HotHead = SpawnActor<AHotHead>();
	HotHead->SetName("HotHead");
	HotHead->SetActorType(EActorType::Monster);
	HotHead->SetActorLocation({ 3000, 350 });
}

void ULevel111::LevelEnd(ULevel* _Level)
{
	Fade->FadeStart(FadeOption::FadeOut);
	
	UContentsHelper::KirbyAbilityType = APlayer::GetMainPlayer()->GetActiveAbility();
	GEngine->DestroyLevel("Level111");
}