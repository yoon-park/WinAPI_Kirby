#include "DisappearEffect.h"

#include "Player.h"

ADisappearEffect::ADisappearEffect()
{

}

ADisappearEffect::~ADisappearEffect()
{

}

void ADisappearEffect::BeginPlay()
{
	AEffect::BeginPlay();

	{
		Renderer = CreateImageRenderer(KirbyRenderOrder::Effect);
		Renderer->SetImage("EffectAbility1_Right.png");
		Renderer->SetTransform({ {0,0}, {256, 256} });

		Renderer->CreateAnimation("Absorb_Effect_Right", "EffectAbility1_Right.png", 8, 10, 0.15f, false);
		Renderer->CreateAnimation("Absorb_Effect_Left", "EffectAbility1_Left.png", 8, 10, 0.15f, false);

		Renderer->ChangeAnimation(GetAnimationName("Absorb_Effect"));
	}
}

void ADisappearEffect::Tick(float _DeltaTime)
{
	AEffect::Tick(_DeltaTime);

	if (Renderer->IsCurAnimationEnd())
	{
		Destroy();
		return;
	}
}