#include "Fire.h"

AFire::AFire()
{

}

AFire::~AFire()
{

}

void AFire::BeginPlay()
{
	AAbility::BeginPlay();

	{
		Renderer = CreateImageRenderer(KirbyRenderOrder::Ability);
		Renderer->SetImage("EffectAbility_Right.png");
		Renderer->SetTransform({ {0,0}, {256, 256} });

		Renderer->CreateAnimation("Fire_Right", "EffectAbility_Right.png", 39, 42, 0.03f, false);
		Renderer->CreateAnimation("Fire_Left", "EffectAbility_Left.png", 39, 42, 0.03f, false);

		Renderer->ChangeAnimation(GetAnimationName("Fire"));
	}
	{
		AttackCollision = CreateCollision(KirbyCollisionOrder::None);
		AttackCollision->SetColType(ECollisionType::CirCle);
		AttackCollision->SetTransform({ {0, -25}, { 50, 0 } });
	}
}

void AFire::Tick(float _DeltaTime)
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

	if (
		(DirState == EActorDir::Left && (OwnerPos.X - AttackPos.X >= 160.0f)) ||
		(DirState == EActorDir::Right && (AttackPos.X - OwnerPos.X >= 160.0f))
		)
	{
		Destroy();
		return;
	}

	AddActorLocation(AttackDir.Normalize2DReturn() * _DeltaTime * 800.0f);
}