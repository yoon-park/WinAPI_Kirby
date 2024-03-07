#include "WaddleDee.h"

#include "Player.h"
#include "Ability.h"

AWaddleDee::AWaddleDee()
{

}

AWaddleDee::~AWaddleDee()
{

}

void AWaddleDee::BeginPlay()
{
	AMonster::BeginPlay();

	{
		Renderer = CreateImageRenderer(KirbyRenderOrder::Monster);
		Renderer->SetImage("NormalEnemy_Left.png");
		Renderer->SetTransform({ {0,0}, {256, 256} });

		Renderer->CreateAnimation("Run_Left", "NormalEnemy_Left.png", 0, 1, 0.15f, true);
		Renderer->CreateAnimation("Run_Right", "NormalEnemy_Right.png", 0, 1, 0.15f, true);

		Renderer->ChangeAnimation("Run_Left");
	}
	{
		BodyCollision = CreateCollision(KirbyCollisionOrder::Monster);
		BodyCollision->SetColType(ECollisionType::Rect);
		BodyCollision->SetScale({ 50, 50 });
	}
}

void AWaddleDee::Tick(float _DeltaTime)
{
	AMonster::Tick(_DeltaTime);

	std::vector<UCollision*> Result;

	if (BodyCollision->CollisionCheck(KirbyCollisionOrder::PlayerAbsorb, Result) == true)
	{
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		APlayer* PlayerAbsorb = dynamic_cast<APlayer*>(Ptr);

		if (PlayerAbsorb == nullptr)
		{
			MsgBoxAssert("PlayerAbsorb가 존재하지 않습니다.");
		}

		Destroy();
	}

	if (BodyCollision->CollisionCheck(KirbyCollisionOrder::PlayerAbility, Result) == true)
	{
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AAbility* PlayerAbility = dynamic_cast<AAbility*>(Ptr);

		if (PlayerAbility == nullptr)
		{
			MsgBoxAssert("PlayerAbility가 존재하지 않습니다.");
		}

		Destroy();
	}
}