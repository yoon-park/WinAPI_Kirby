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
			MsgBoxAssert("�浹�� nullptr�� ��찡 �����մϴ�.");
		}

		delete Collision;
		Collision = nullptr;
	}

	Collisions.clear();

	for (UImageRenderer* ImageRenderer : Renderers)
	{
		if (ImageRenderer == nullptr)
		{
			MsgBoxAssert("�̹��� �������� nullptr�� ��찡 �����մϴ�.");
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

void AActor::ActiveUpdate(float _DeltaTime)
{
	UTickObject::ActiveUpdate(_DeltaTime);

	for (UImageRenderer* Renderer : Renderers)
	{
		Renderer->ActiveUpdate(_DeltaTime);
	}
}

void AActor::Destroy(float _DestroyTime)
{
	UTickObject::Destroy(_DestroyTime);

	for (UImageRenderer* Renderer : Renderers)
	{
		Renderer->Destroy(_DestroyTime);
	}
}

void AActor::DestroyUpdate(float _DeltaTime)
{
	UTickObject::DestroyUpdate(_DeltaTime);

	for (UImageRenderer* Renderer : Renderers)
	{
		Renderer->DestroyUpdate(_DeltaTime);
	}
}