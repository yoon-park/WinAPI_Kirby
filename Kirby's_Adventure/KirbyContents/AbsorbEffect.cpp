#include "AbsorbEffect.h"

#include "Player.h"

AAbsorbEffect::AAbsorbEffect()
{

}

AAbsorbEffect::~AAbsorbEffect()
{

}

void AAbsorbEffect::BeginPlay()
{
	AEffect::BeginPlay();

	{
		Renderer = CreateImageRenderer(KirbyRenderOrder::Effect);
		Renderer->SetImage("EffectAbility1_Right.png");
		Renderer->SetTransform({ {0,0}, {256, 256} });

		Renderer->CreateAnimation("Absorb_Effect_Right", "EffectAbility1_Right.png", 3, 3, 0.1f, false);
		Renderer->CreateAnimation("Absorb_Effect_Left", "EffectAbility1_Left.png", 3, 3, 0.1f, false);

		Renderer->ChangeAnimation(GetAnimationName("Absorb_Effect"));
	}
	{
		EffectCollision = CreateCollision(KirbyCollisionOrder::None);
		EffectCollision->SetColType(ECollisionType::CirCle);
		EffectCollision->SetTransform({ {0, -25}, { 10, 0 } });
	}
}

void AAbsorbEffect::Tick(float _DeltaTime)
{
	AEffect::Tick(_DeltaTime);

	APlayer* Player = APlayer::GetMainPlayer();

	if(Player->GetAbsorbActive() == false)
	{
		Destroy();
		return;
	}

	std::vector<UCollision*> Result;
	if (EffectCollision->CollisionCheck(KirbyCollisionOrder::Player, Result) == true)
	{
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		APlayer* Player = dynamic_cast<APlayer*>(Ptr);

		if (Player == nullptr)
		{
			MsgBoxAssert("Player가 존재하지 않습니다.");
		}

		Destroy();
		return;
	}

	AddActorLocation(Player->GetLocationDifference());

	FVector PlayerPos = { Owner->GetActorLocation().X, Owner->GetActorLocation().Y - 20 };
	FVector EffectPos = GetActorLocation();
	FVector EffectDir = PlayerPos - EffectPos;
	FVector EffectDirNormal = EffectDir.Normalize2DReturn();

	MoveVector += EffectDirNormal * _DeltaTime * 5000.0f;
	AddActorLocation(MoveVector * _DeltaTime);
}