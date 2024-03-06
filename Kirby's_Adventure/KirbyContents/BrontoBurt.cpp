#include "BrontoBurt.h"

#include "Player.h"

ABrontoBurt::ABrontoBurt()
{

}

ABrontoBurt::~ABrontoBurt()
{

}

void ABrontoBurt::BeginPlay()
{
	AMonster::BeginPlay();

	{
		Renderer = CreateImageRenderer(KirbyRenderOrder::Monster);
		Renderer->SetImage("NormalEnemy_Left.png");
		Renderer->SetTransform({ {0,0}, {256, 256} });

		Renderer->CreateAnimation("Run_Left", "NormalEnemy_Left.png", 29, 30, 0.15f, true);
		Renderer->CreateAnimation("Run_Right", "NormalEnemy_Right.png", 29, 30, 0.15f, true);

		Renderer->ChangeAnimation("Run_Left");
	}

	{
		BodyCollision = CreateCollision(KirbyCollisionOrder::Monster);
		BodyCollision->SetColType(ECollisionType::Rect);
		BodyCollision->SetScale({ 50, 50 });
	}
}

void ABrontoBurt::Tick(float _DeltaTime)
{
	AMonster::Tick(_DeltaTime);

	std::vector<UCollision*> Result;
	if (BodyCollision->CollisionCheck(KirbyCollisionOrder::PlayerAbility, Result) == true)
	{
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		APlayer* Player = dynamic_cast<APlayer*>(Ptr);

		if (Player == nullptr)
		{
			MsgBoxAssert("플레이어가 존재하지 않습니다.");
		}

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
	FVector MonsterDirNormal = MonsterDir.Normalize2DReturn();

	AddActorLocation(MonsterDirNormal * _DeltaTime * 100.0f);
}