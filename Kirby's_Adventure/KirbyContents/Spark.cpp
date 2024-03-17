#include "Spark.h"

ASpark::ASpark()
{

}

ASpark::~ASpark()
{

}

void ASpark::BeginPlay()
{
	AAbility::BeginPlay();

	{
		Renderer = CreateImageRenderer(KirbyRenderOrder::Ability);
		Renderer->SetImage("EffectAbility1_Right.png");
		Renderer->SetTransform({ {0,0}, {256, 256} });

		Renderer->CreateAnimation("Spark_Right", "EffectAbility1_Right.png", 36, 38, 0.03f, false);
		Renderer->CreateAnimation("Spark_Left", "EffectAbility1_Left.png", 36, 38, 0.03f, false);

		Renderer->ChangeAnimation(GetAnimationName("Spark"));
	}
	{
		AttackCollision = CreateCollision(KirbyCollisionOrder::None);
		AttackCollision->SetColType(ECollisionType::CirCle);
		AttackCollision->SetTransform({ {0, -25}, { 50, 0 } });
	}
}

void ASpark::Tick(float _DeltaTime)
{
	AAbility::Tick(_DeltaTime);

	if (AttackCollision->GetOrder() == static_cast<int>(KirbyCollisionOrder::None))
	{
		if (Owner->GetActorType() == EActorType::Monster)
		{
			AttackCollision->SetOrder(static_cast<int>(KirbyCollisionOrder::MonsterAbilty));
		}
		else if (Owner->GetActorType() == EActorType::Player)
		{
			AttackCollision->SetOrder(static_cast<int>(KirbyCollisionOrder::PlayerAbility));
		}
	}

	if (Renderer->IsCurAnimationEnd())
	{
		Destroy();
		return;
	}

	FVector OwnerPos = Owner->GetActorLocation();
	FVector AttackPos = GetActorLocation();
	FVector AttackDir = AttackPos - OwnerPos;

	AddActorLocation(AttackDir.Normalize2DReturn() * _DeltaTime * 300.0f);
}