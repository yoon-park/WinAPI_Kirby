#include "Monster.h"

#include "Player.h"

AMonster::AMonster()
{

}

AMonster::~AMonster()
{

}

void AMonster::BeginPlay()
{
	AActor::BeginPlay();

	{
		UImageRenderer* Renderer = CreateImageRenderer(KirbyRenderOrder::Monster);
		Renderer->SetImage("Enemy.png");
		Renderer->SetTransform({ {0,0}, {50, 50} });
	}

	{
		BodyCollision = CreateCollision(KirbyCollisionOrder::Player);
		BodyCollision->SetScale({ 50, 50 });
	}
}

void AMonster::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> Result;
	if (BodyCollision->CollisionCheck(KirbyCollisionOrder::Player, Result) == true)
	{
		Destroy();
	}

	APlayer* Player = APlayer::GetMainPlayer();
	if (Player == nullptr)
	{
		MsgBoxAssert("플레이어가 존재하지 않습니다.");
	}

	FVector PlayerPos = Player->GetActorLocation();
	FVector MonsterPos = GetActorLocation();

	FVector MonsterDir = PlayerPos - MonsterPos;
	MonsterDir.Y = 0.0f;
	FVector MonsterDirNormal = MonsterDir.Normalize2DReturn();

	AddActorLocation(MonsterDirNormal * _DeltaTime * 300.0f);
}