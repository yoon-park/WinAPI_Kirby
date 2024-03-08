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
}