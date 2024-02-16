#include "Actor.h"

AActor::AActor()
{

}

AActor::~AActor()
{
	for (UCollision* Collision : Collisions)
	{
		if (Collision == nullptr)
		{
			MsgBoxAssert("충돌이 nullptr인 경우가 존재합니다.");
		}

		delete Collision;
		Collision = nullptr;
	}

	Collisions.clear();

	for (UImageRenderer* ImageRenderer : Renderers)
	{
		if (ImageRenderer == nullptr)
		{
			MsgBoxAssert("이미지 렌더러가 nullptr인 경우가 존재합니다.");
		}

		delete ImageRenderer;
		ImageRenderer = nullptr;
	}

	Renderers.clear();
}

void AActor::Tick(float _DeltaTime)
{
	UTickObject::Tick(_DeltaTime);
	ActiveUpdate(_DeltaTime);
	DestroyUpdate(_DeltaTime);
}

UCollision* AActor::CreateCollision(int _Order)
{
	UCollision* Component = new UCollision();
	UActorComponent* ActorCom = Component;

	ActorCom->SetOwner(this);
	ActorCom->SetOrder(_Order);
	ActorCom->BeginPlay();
	Collisions.push_back(Component);

	return Component;
}

UImageRenderer* AActor::CreateImageRenderer(int _Order)
{
	UImageRenderer* Component = new UImageRenderer();
	UActorComponent* ActorCom = Component;

	ActorCom->SetOwner(this);
	ActorCom->SetOrder(_Order);
	ActorCom->BeginPlay();
	Renderers.push_back(Component);

	return Component;
}

void AActor::AllRenderersActiveOff()
{
	for (UImageRenderer* Renderer : Renderers)
	{
		Renderer->ActiveOff();
	}
}

void AActor::AllRenderersActiveOn()
{
	for (UImageRenderer* Renderer : Renderers)
	{
		Renderer->ActiveOn();
	}
}

void AActor::ActiveUpdate(float _DeltaTime)
{
	UTickObject::ActiveUpdate(_DeltaTime);

	for (UImageRenderer* Renderer : Renderers)
	{
		Renderer->ActiveUpdate(_DeltaTime);
	}

	for (UCollision* Collision : Collisions)
	{
		Collision->ActiveUpdate(_DeltaTime);
	}
}

void AActor::Destroy(float _DestroyTime)
{
	UTickObject::Destroy(_DestroyTime);

	for (UImageRenderer* Renderer : Renderers)
	{
		Renderer->Destroy(_DestroyTime);
	}

	for (UCollision* Collision : Collisions)
	{
		Collision->Destroy(_DestroyTime);
	}
}

void AActor::DestroyUpdate(float _DeltaTime)
{
	UTickObject::DestroyUpdate(_DeltaTime);

	for (UImageRenderer* Renderer : Renderers)
	{
		Renderer->DestroyUpdate(_DeltaTime);
	}

	for (UCollision* Collision : Collisions)
	{
		Collision->DestroyUpdate(_DeltaTime);
	}
}

void AActor::CheckReleaseChild()
{
	{
		std::list<UImageRenderer*>::iterator StartIter = Renderers.begin();
		std::list<UImageRenderer*>::iterator EndIter = Renderers.end();

		for (; StartIter != EndIter;)
		{
			UImageRenderer* Renderer = StartIter.operator*();

			if (Renderer == nullptr)
			{
				MsgBoxAssert("Renderer가 nullptr인 경우가 존재합니다.");
				return;
			}

			if (Renderer->IsDestroy() == false)
			{
				++StartIter;
				continue;
			}

			delete Renderer;
			Renderer = nullptr;
			StartIter = Renderers.erase(StartIter);
		}
	}

	{
		std::list<UCollision*>::iterator StartIter = Collisions.begin();
		std::list<UCollision*>::iterator EndIter = Collisions.end();

		for (; StartIter != EndIter;)
		{
			UCollision* Collision = StartIter.operator*();

			if (Collision == nullptr)
			{
				MsgBoxAssert("Collision이 nullptr인 경우가 존재합니다.");
				return;
			}

			if (Collision->IsDestroy() == false)
			{
				++StartIter;
				continue;
			}

			delete Collision;
			Collision = nullptr;
			StartIter = Collisions.erase(StartIter);
		}
	}
}