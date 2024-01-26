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

void ULevel::ActorInit(AActor* _NewActor)
{
	_NewActor->SetWorld(this);
	_NewActor->BeginPlay();
}

void ULevel::LevelTick(float _DeltaTime)
{
	for (std::pair<const int, std::list<AActor*>>& OrderListPair : AllActor)
	{
		std::list<AActor*>& ActorList = OrderListPair.second;
		for (AActor* Actor : ActorList)
		{
			if (Actor->IsActive() == false)
			{
				continue;
			}

			Actor->DestroyUpdate(_DeltaTime);
			Actor->Tick(_DeltaTime);
		}
	}
}

void ULevel::LevelRender(float _DeltaTime)
{
	for (std::pair<const int, std::list<UImageRenderer*>>& OrderListPair : Renderers)
	{
		std::list<UImageRenderer*>& RendererList = OrderListPair.second;
		for (UImageRenderer* Renderer : RendererList)
		{
			if (Renderer->IsActive() == false)
			{
				continue;
			}

			Renderer->Render(_DeltaTime);
		}
	}

}

void ULevel::LevelRelease(float _DeltaTime)
{
	for (std::pair<const int, std::list<AActor*>>& OrderListPair : AllActor)
	{
		std::list<AActor*>& ActorList = OrderListPair.second;

		std::list<AActor*>::iterator StartIter = ActorList.begin();
		std::list<AActor*>::iterator EndIter = ActorList.end();

		for (; StartIter != EndIter;)
		{
			AActor* Actor = StartIter.operator*();

			if (Actor == nullptr)
			{
				MsgBoxAssert("Actor가 nullptr인 경우가 존재했습니다");
				return;
			}

			if (Actor->IsDestroy() == false)
			{
				++StartIter;
				continue;
			}

			delete Actor;
			Actor = nullptr;
			StartIter = ActorList.erase(StartIter);
		}
	}
}