#include "Actor.h"

AActor::AActor()
{

}

AActor::~AActor()
{
	for (UImageRenderer* ImageRenderer : Renderers)
	{
		if (ImageRenderer == nullptr)
		{
			MsgBoxAssert("이미지 렌더러가 nullptr입니다.");
		}

		delete ImageRenderer;
		ImageRenderer = nullptr;
	}

	Renderers.clear();
}

void AActor::Tick(float _DeltaTime)
{
	UTickObject::Tick(_DeltaTime);
	DestroyUpdate(_DeltaTime);
}

UImageRenderer* AActor::CreateImageRenderer(int Order)
{
	UImageRenderer* NewRenderer = new UImageRenderer();
	UActorComponent* ActorCom = NewRenderer;

	ActorCom->SetOwner(this);
	ActorCom->SetOrder(Order);
	ActorCom->BeginPlay();
	Renderers.push_back(NewRenderer);

	return NewRenderer;
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