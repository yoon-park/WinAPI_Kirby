#include "SpitStar.h"

#include "Monster.h"
#include "DisappearEffect.h"

ASpitStar::ASpitStar()
{

}

ASpitStar::~ASpitStar()
{

}

void ASpitStar::BeginPlay()
{
	AAbility::BeginPlay();

	{
		Renderer = CreateImageRenderer(KirbyRenderOrder::Ability);
		Renderer->SetImage("EffectAbility1_Right.png");
		Renderer->SetTransform({ {0,0}, {256, 256} });

		Renderer->CreateAnimation("SpitStar_Right", "EffectAbility1_Right.png", 4, 7, 0.1f, true);
		Renderer->CreateAnimation("SpitStar_Left", "EffectAbility1_Left.png", 4, 7, 0.1f, true);

		Renderer->ChangeAnimation(GetAnimationName("SpitStar"));
	}
	{
		AttackCollision = CreateCollision(KirbyCollisionOrder::PlayerAbility);
		AttackCollision->SetColType(ECollisionType::Rect);
		AttackCollision->SetTransform({ {0, -25}, { 50, 50 } });
	}
}

void ASpitStar::Tick(float _DeltaTime)
{
	AAbility::Tick(_DeltaTime);

	if (IsWallCheck() == true)
	{
		ADisappearEffect* DisappearEffect = GetWorld()->SpawnActor<ADisappearEffect>();
		DisappearEffect->SetActorType(EActorType::Effect);
		DisappearEffect->SetActorLocation(GetActorLocation());

		Destroy();
		return;
	}

	AddActorLocation(MoveVector * _DeltaTime);
}

bool ASpitStar::IsWallCheck()
{
	FVector CheckPosTop = { GetActorLocation().X, GetActorLocation().Y - 50 };
	FVector CheckPosCenter = { GetActorLocation().X, GetActorLocation().Y - 26 };
	FVector CheckPosBottom = { GetActorLocation().X, GetActorLocation().Y - 2 };

	switch (DirState)
	{
	case EActorDir::Left:
		CheckPosTop.X -= 25;
		CheckPosCenter.X -= 25;
		CheckPosBottom.X -= 25;
		break;
	case EActorDir::Right:
		CheckPosTop.X += 25;
		CheckPosCenter.X += 25;
		CheckPosBottom.X += 25;
		break;
	default:
		break;
	}

	Color8Bit ColorTop = UContentsHelper::ColMapImage->GetColor(CheckPosTop.iX(), CheckPosTop.iY(), Color8Bit::MagentaA);
	Color8Bit ColorCenter = UContentsHelper::ColMapImage->GetColor(CheckPosCenter.iX(), CheckPosCenter.iY(), Color8Bit::MagentaA);
	Color8Bit ColorBottom = UContentsHelper::ColMapImage->GetColor(CheckPosBottom.iX(), CheckPosBottom.iY(), Color8Bit::MagentaA);
	if (
		ColorTop == Color8Bit(255, 0, 255, 0) ||
		ColorCenter == Color8Bit(255, 0, 255, 0) ||
		ColorBottom == Color8Bit(255, 0, 255, 0)
		)
	{
		return true;
	}

	return false;
}

void ASpitStar::SetDirState(EActorDir _DirState)
{
	AAbility::SetDirState(_DirState);

	if (DirState == EActorDir::Left)
	{
		MoveVector = FVector::Left * 650.0f;
	}
	else if (DirState == EActorDir::Right)
	{
		MoveVector = FVector::Right * 650.0f;
	}
}