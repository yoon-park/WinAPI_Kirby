#include "TitleLevel.h"

#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include <EnginePlatform\EngineInput.h>
#include <EngineCore\EngineCore.h>
#include <EngineCore\EngineResourcesManager.h>
#include "TitleLogo.h"
#include "TitleKirby.h"
#include "Level111.h"
#include "Level141.h"

UTitleLevel::UTitleLevel()
{

}

UTitleLevel::~UTitleLevel()
{

}

void UTitleLevel::BeginPlay()
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

		UEngineResourcesManager::GetInst().CuttingImage("Kirby1_Left.png", 10, 7);			// 256 * 256
		UEngineResourcesManager::GetInst().CuttingImage("Kirby1_Right.png", 10, 7);			// 256 * 256
		UEngineResourcesManager::GetInst().CuttingImage("Kirby2_Left.png", 10, 4);			// 256 * 256
		UEngineResourcesManager::GetInst().CuttingImage("Kirby2_Right.png", 10, 4);			// 256 * 256
		//UEngineResourcesManager::GetInst().CuttingImage("Kirby3_Left.png", 10, 4);			// 256 * 256
		//UEngineResourcesManager::GetInst().CuttingImage("Kirby3_Right.png", 10, 4);			// 256 * 256
		UEngineResourcesManager::GetInst().CuttingImage("EffectAbility1_Left.png", 10, 6);	// 256 * 256
		UEngineResourcesManager::GetInst().CuttingImage("EffectAbility1_Right.png", 10, 6);	// 256 * 256
		UEngineResourcesManager::GetInst().CuttingImage("EffectAbility2_Left.png", 10, 1);	// 256 * 256
		UEngineResourcesManager::GetInst().CuttingImage("EffectAbility2_Right.png", 10, 1);	// 256 * 256
		UEngineResourcesManager::GetInst().CuttingImage("NormalEnemy_Left.png", 10, 7);		// 256 * 256
		UEngineResourcesManager::GetInst().CuttingImage("NormalEnemy_Right.png", 10, 7);	// 256 * 256
		UEngineResourcesManager::GetInst().CuttingImage("PowerEnemy1_Left.png", 10, 9);		// 256 * 256
		UEngineResourcesManager::GetInst().CuttingImage("PowerEnemy1_Right.png", 10, 9);	// 256 * 256
		//UEngineResourcesManager::GetInst().CuttingImage("PowerEnemy2_Left.png", 10, 9);		// 256 * 256
		//UEngineResourcesManager::GetInst().CuttingImage("PowerEnemy2_Right.png", 10, 9);		// 256 * 256
		UEngineResourcesManager::GetInst().CuttingImage("MidBossEnemy_Left.png", 10, 4);	// 256 * 256
		UEngineResourcesManager::GetInst().CuttingImage("MidBossEnemy_Right.png", 10, 4);	// 256 * 256
		UEngineResourcesManager::GetInst().CuttingImage("BossEnemy_Left.png", 5, 2);		// 256 * 1024
		UEngineResourcesManager::GetInst().CuttingImage("HUDUI.png", 1, 5);					// 1024 * 256
		UEngineResourcesManager::GetInst().CuttingImage("HUDAbility.png", 10, 2);			// 256 * 256
		UEngineResourcesManager::GetInst().CuttingImage("HUDComponent.png", 10, 2);			// 128 * 128
		UEngineResourcesManager::GetInst().CuttingImage("Item_Left.png", 10, 3);			// 300 * 300
		UEngineResourcesManager::GetInst().CuttingImage("Item_Right.png", 10, 3);			// 300 * 300
	}

	GEngine->CreateLevel<ULevel111>("Level111");
	SetNextLevel("Level111");
	//GEngine->CreateLevel<ULevel141>("Level141");
	//SetNextLevel("Level141");
}

void UTitleLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (UEngineInput::IsDown('P'))
	{
		GEngine->ChangeLevel("Level111");
	}
}

void UTitleLevel::LevelStart(ULevel* _Level)
{
	UEngineDirectory NewPath;

	NewPath.MoveParent();
	NewPath.Move("Resources");
	NewPath.Move("TitleLevel");

	std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);

	for (UEngineFile& File : AllFileList)
	{
		std::string FullPath = File.GetFullPath();
		UEngineResourcesManager::GetInst().LoadImg(FullPath);
	}

	UEngineResourcesManager::GetInst().CuttingImage("TitleKirby.png", 5, 3);

	ATitleLogo* Logo = SpawnActor<ATitleLogo>();
	ATitleKirby* Kirby = SpawnActor<ATitleKirby>();
}
void UTitleLevel::LevelEnd(ULevel* _Level)
{

}