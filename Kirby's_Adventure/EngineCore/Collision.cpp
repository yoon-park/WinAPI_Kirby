#include "Collision.h"

#include <map>
#include <list>

#include "EngineCore.h"
#include "Actor.h"
#include "Level.h"

UCollision::UCollision()
{
}

UCollision::~UCollision()
{
}

void UCollision::SetOrder(int _Order)
{
	AActor* Owner = GetOwner();
	ULevel* Level = Owner->GetWorld();

	std::map<int, std::list<UCollision*>>& Collisions = Level->Collisions;
	
	Collisions[GetOrder()].remove(this);
	UTickObject::SetOrder(_Order);
	Collisions[GetOrder()].push_back(this);
}

bool UCollision::CollisionCheck(int _Order, std::vector<UCollision*>& _Result)
{
	AActor* Owner = GetOwner();
	ULevel* Level = Owner->GetWorld();

	std::list<UCollision*>& Collisions = Level->Collisions[_Order];

	FTransform ThisTransform = GetActorBaseTransform();

	for (UCollision* _OtherCollision : Collisions)
	{
		FTransform OtherTransform = _OtherCollision->GetActorBaseTransform();

		if (ThisTransform.Collision(ColType, _OtherCollision->ColType, OtherTransform) == true)
		{
			_Result.push_back(_OtherCollision);
		}
	}

	return _Result.empty() == false;
}

void UCollision::DebugRender(FVector _CameraPos)
{
	FTransform ThisTransform = GetActorBaseTransform();
	ThisTransform.AddPosition(-_CameraPos);

	switch (ColType)
	{
	case ECollisionType::Point:
	{
		ThisTransform.SetScale({ 10, 10 });
		GEngine->MainWindow.GetBackBufferImage()->DrawEllipse(ThisTransform);
		break;
	}
	case ECollisionType::CirCle:
	{
		GEngine->MainWindow.GetBackBufferImage()->DrawEllipse(ThisTransform);
		break;
	}
	case ECollisionType::Rect:
	{
		GEngine->MainWindow.GetBackBufferImage()->DrawRectangle(ThisTransform);
		break;
	}
	default:
		break;
	}
}

void UCollision::BeginPlay()
{
	USceneComponent::BeginPlay();
}