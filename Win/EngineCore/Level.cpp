#include "Level.h"

#include "Actor.h"

ULevel::ULevel()
{

}

ULevel::~ULevel()
{
	for (std::pair<const int, std::list<AActor*>>& OrderListPair : AllActor)
	{
		std::list<AActor*>& ActorList = OrderListPair.second;
		for (AActor* Actor : ActorList)
		{
			if (Actor == nullptr)
			{
				continue;
			}

			delete Actor;
			Actor = nullptr;
		}
	}
}

void ULevel::BeginPlay()
{

}

void ULevel::Tick(float _DeltaTime)
{

}

void ULevel::ActorTick(float _DeltaTime)
{
	for (std::pair<const int, std::list<AActor*>>& OrderListPair : AllActor)
	{
		std::list<AActor*>& ActorList = OrderListPair.second;
		for (AActor* Actor : ActorList)
		{
			if (false == Actor->IsOn())
			{
				continue;
			}

			Actor->Tick(_DeltaTime);
		}
	}
}

void ULevel::ActorInit(AActor* _NewActor)
{
	_NewActor->SetWorld(this);
	_NewActor->BeginPlay();
}