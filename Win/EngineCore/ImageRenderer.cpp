#include "ImageRenderer.h"

#include "EngineCore.h"
#include "EngineResourcesManager.h"
#include "Actor.h"

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

void UImageRenderer::SetImage(std::string_view _Name)
{
	Image = UEngineResourcesManager::GetInst().FindImg(_Name);

	if (Image == nullptr)
	{
		MsgBoxAssert(std::string(_Name) + "이미지가 존재하지 않습니다.");
		return;
	}
}

void UImageRenderer::Render(float _DeltaTime)
{
	if (Image == nullptr)
	{
		MsgBoxAssert("이미지가 존재하지 않는 렌더러입니다.");
	}

	FTransform ThisTrans = GetTransform();
	FTransform OwnerTrans = GetOwner()->GetTransform();
	ThisTrans.AddPosition(OwnerTrans.GetPosition());

	GEngine->MainWindow.GetBackBufferImage()->TransCopy(Image, ThisTrans, ImageCuttingTransform);
}

void UImageRenderer::BeginPlay()
{
	USceneComponent::BeginPlay();
}