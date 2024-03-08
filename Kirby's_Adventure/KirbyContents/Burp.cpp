#include "Burp.h"

#include "Monster.h"

ABurp::ABurp()
{

}

ABurp::~ABurp()
{

}

void ABurp::BeginPlay()
{
	AAbility::BeginPlay();
	
	{
		Renderer = CreateImageRenderer(KirbyRenderOrder::Ability);
		Renderer->SetImage("EffectAbility_Right.png");
		Renderer->SetTransform({ {0,0}, {256, 256} });

		Renderer->CreateAnimation("Burp_Right", "EffectAbility_Right.png", 2, 2, 0.1f, false);
		Renderer->CreateAnimation("Burp_Left", "EffectAbility_Left.png", 2, 2, 0.1f, false);

		Renderer->ChangeAnimation(GetAnimationName("Burp"));
	}
	{
		AttackCollision = CreateCollision(KirbyCollisionOrder::PlayerAbility);
		AttackCollision->SetColType(ECollisionType::Rect);
		AttackCollision->SetTransform({ {0, -24}, { 50, 47 } });
	}

	DirCheck();
	if (DirState == EActorDir::Left)
	{
		MoveVector = FVector::Left * 1000.0f;
		MoveAcc = FVector::Right * 2500.0f;
	}
	else if (DirState == EActorDir::Right)
	{
		MoveVector = FVector::Right * 1000.0f;
		MoveAcc = FVector::Left * 2500.0f;
	}
}

void ABurp::Tick(float _DeltaTime)
{
	AAbility::Tick(_DeltaTime);

	std::vector<UCollision*> Result;
	if (AttackCollision->CollisionCheck(KirbyCollisionOrder::Monster, Result) == true)
	{
		UCollision* Collision = Result[0];
		AActor* Ptr = Collision->GetOwner();
		AMonster* Monster = dynamic_cast<AMonster*>(Ptr);

		if (Monster == nullptr)
		{
			MsgBoxAssert("Monster가 존재하지 않습니다.");
		}

		Monster->Destroy();
		Destroy();
	}

	if (
		DirState == EActorDir::Left && MoveVector.X > 0.0f || 
		DirState == EActorDir::Right && MoveVector.X < 0.0f ||
		IsWallCheck() == true
		)
	{
		Destroy();
	}

	MoveVector += MoveAcc * _DeltaTime;
	AddActorLocation(MoveVector * _DeltaTime);
}

bool ABurp::IsWallCheck()
{
	FVector CheckPosTop = { GetActorLocation().X, GetActorLocation().Y - 47};
	FVector CheckPosCenter = { GetActorLocation().X, GetActorLocation().Y - 24};
	FVector CheckPosBottom = { GetActorLocation().X, GetActorLocation().Y - 1};

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