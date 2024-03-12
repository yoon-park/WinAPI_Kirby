#include "Level111.h"

#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore\EngineResourcesManager.h>
#include "Level112.h"
#include "BackGroundMap.h"
#include "HUD.h"
#include "FadeOut.h"
#include "Player.h"
#include "WaddleDee.h"
#include "BrontoBurt.h"
#include "Sparky.h"

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

		UEngineResourcesManager::GetInst().CuttingImage("Kirby1_Left.png", 10, 7);
		UEngineResourcesManager::GetInst().CuttingImage("Kirby1_Right.png", 10, 7);
		UEngineResourcesManager::GetInst().CuttingImage("Kirby2_Left.png", 10, 4);
		UEngineResourcesManager::GetInst().CuttingImage("Kirby2_Right.png", 10, 4);
		UEngineResourcesManager::GetInst().CuttingImage("EffectAbility_Left.png", 10, 6);
		UEngineResourcesManager::GetInst().CuttingImage("EffectAbility_Right.png", 10, 6);
		UEngineResourcesManager::GetInst().CuttingImage("NormalEnemy_Left.png", 10, 7);
		UEngineResourcesManager::GetInst().CuttingImage("NormalEnemy_Right.png", 10, 7);
		UEngineResourcesManager::GetInst().CuttingImage("PowerEnemy1_Left.png", 10, 9);
		UEngineResourcesManager::GetInst().CuttingImage("PowerEnemy1_Right.png", 10, 9);
	}

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
	Map->SetMapImage("Stage2-3.png");
	Map->SetColMapImage("Stage2-3_Col.png");

	Fade = SpawnActor<AFadeOut>();
	Fade->SetActorLocation({ 400, 375 });
	Fade->SetActive(true, 0.5f);
	Fade->FadeStart(FadeOption::FadeIn);

	AHUD* HUD = SpawnActor<AHUD>();

	APlayer* Kirby = SpawnActor<APlayer>();
	Kirby->SetName("Kirby");
	Kirby->SetActorType(EActorType::Player);
	Kirby->SetActorLocation({ 200, 200 });

	AWaddleDee* WaddleDee = SpawnActor<AWaddleDee>();
	WaddleDee->SetName("WaddleDee");
	WaddleDee->SetActorType(EActorType::Monster);
	WaddleDee->SetActorLocation({ 1500, 350 });

	ABrontoBurt* BrontoBurt = SpawnActor<ABrontoBurt>();
	BrontoBurt->SetName("BrontoBurt");
	BrontoBurt->SetActorType(EActorType::Monster);
	BrontoBurt->SetActorLocation({ 2000, 200 });

	ASparky* Sparky = SpawnActor<ASparky>();
	Sparky->SetName("Sparky");
	Sparky->SetActorType(EActorType::Monster);
	Sparky->SetActorLocation({ 500, 350 });
}

void ULevel111::LevelEnd(ULevel* _Level)
{
	Fade->FadeStart(FadeOption::FadeOut);
	
	GEngine->DestroyLevel("Level111");
}