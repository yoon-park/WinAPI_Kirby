#include "AbilityStarEffect.h"

#include "Player.h"
#include "DisappearEffect.h"

AAbilityStarEffect::AAbilityStarEffect()
{

}

AAbilityStarEffect::~AAbilityStarEffect()
{

}

void AAbilityStarEffect::BeginPlay()
{
	AEffect::BeginPlay();

	{
		Renderer = CreateImageRenderer(KirbyRenderOrder::Effect);
		Renderer->SetImage("EffectAbility1_Right.png");
		Renderer->SetTransform({ {0,0}, {256, 256} });

		Renderer->CreateAnimation("Absorb_Effect_Right", "EffectAbility1_Right.png", 4, 7, 0.1f, false);
		Renderer->CreateAnimation("Absorb_Effect_Left", "EffectAbility1_Left.png", 4, 7, 0.1f, false);

		Renderer->ChangeAnimation(GetAnimationName("Absorb_Effect"));
	}
}

void AAbilityStarEffect::Tick(float _DeltaTime)
{
	AEffect::Tick(_DeltaTime);

	APlayer* Player = APlayer::GetMainPlayer();

	if (AnimationTimer <= 0.0f)
	{
		ADisappearEffect* DisappearEffect = GetWorld()->SpawnActor<ADisappearEffect>();
		DisappearEffect->SetActorType(EActorType::Effect);
		DisappearEffect->SetActorLocation(GetActorLocation());

		Destroy();
		return;
	}
	AnimationTimer -= _DeltaTime;

	MoveVector += EffectDirNormal * _DeltaTime * 5000.0f;
	AddActorLocation(MoveVector * _DeltaTime);
}

void AAbilityStarEffect::SetEffectDirNormal(FVector _EffectDirNormal)
{
	EffectDirNormal = _EffectDirNormal;
}