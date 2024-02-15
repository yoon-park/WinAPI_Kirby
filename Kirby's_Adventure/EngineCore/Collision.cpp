#include "Collision.h"

#include <map>
#include <list>

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

void UCollision::BeginPlay()
{
	USceneComponent::BeginPlay();
}