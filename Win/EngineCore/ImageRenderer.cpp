#include "ImageRenderer.h"

#include "EngineCore.h"
#include "Actor.h"
#include "Level.h"

UImageRenderer::UImageRenderer()
{

}

UImageRenderer::~UImageRenderer()
{

}

void UImageRenderer::SetOrder(int _Order)
{
	AActor* Owner = GetOwner();
	ULevel* Level = Owner->GetWorld();

	std::map<int, std::list<UImageRenderer*>>& Renderers = Level->Renderers;
	Renderers[GetOrder()].remove(this);

	UTickObject::SetOrder(_Order);


	Renderers[GetOrder()].push_back(this);
}

void UImageRenderer::Render(float _DeltaTime)
{
	HDC WindowDC = GEngine->MainWindow.GetWindowDC();
	FTransform ThisTrans = GetTransform();
	FTransform OwnerTrans = GetOwner()->GetTransform();
	ThisTrans.AddPosition(OwnerTrans.GetPosition());

	Rectangle(WindowDC, ThisTrans.iLeft(), ThisTrans.iTop(), ThisTrans.iRight(), ThisTrans.iBottom());
}

void UImageRenderer::BeginPlay()
{
	USceneComponent::BeginPlay();
}