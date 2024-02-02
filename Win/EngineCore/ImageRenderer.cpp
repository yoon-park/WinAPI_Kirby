#include "ImageRenderer.h"

#include "EngineCore.h"
#include "EngineResourcesManager.h"
#include "Actor.h"

int UAnimationInfo::Update(float _DeltaTime)
{
	CurTime -= _DeltaTime;

	if (CurTime <= 0.0f)
	{
		CurTime = Times[CurFrame];
		++CurFrame;
	}

	if (CurFrame >= Indexs.size())
	{
		if (Loop == true)
		{
			CurFrame = 0;
		}
		else
		{
			--CurFrame;
		}
	}

	int Index = Indexs[CurFrame];

	return Index;
}

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

void UImageRenderer::SetImage(std::string_view _Name, int _InfoIndex)
{
	Image = UEngineResourcesManager::GetInst().FindImg(_Name);

	if (Image == nullptr)
	{
		MsgBoxAssert(std::string(_Name) + "이미지가 존재하지 않습니다.");
		return;
	}

	InfoIndex = _InfoIndex;
}

void UImageRenderer::CreateAnimation(
	std::string_view _AnimationName,
	std::string_view _ImageName,
	int _Start,
	int _End,
	float _Inter,
	bool _Loop
)
{
	UWindowImage* FindImage = UEngineResourcesManager::GetInst().FindImg(_ImageName);

	if (FindImage == nullptr)
	{
		MsgBoxAssert(std::string(_ImageName) + "이미지가 존재하지 않습니다.");
		return;
	}

	std::string UpperAniName = UEngineString::ToUpper(_AnimationName);

	if (AnimationInfos.contains(UpperAniName) == true)
	{
		MsgBoxAssert(std::string(UpperAniName) + "라는 이름의 애니메이션이 이미 존재합니다.");
		return;
	}

	UAnimationInfo& Info = AnimationInfos[UpperAniName];
	Info.Image = FindImage;
	Info.CurFrame = 0;
	Info.Start = _Start;
	Info.End = _End;
	Info.CurTime = 0.0f;
	Info.Loop = _Loop;

	int Size = Info.End - Info.Start;
	Info.Times.reserve(Size);
	Info.Indexs.reserve(Size);

	for (int i = _Start; i <= _End; i++)
	{
		Info.Times.push_back(_Inter);
	}

	for (int i = _Start; i <= _End; i++)
	{
		Info.Indexs.push_back(i);
	}
}

void UImageRenderer::ChangeAnimation(std::string_view _AnimationName)
{
	std::string UpperAniName = UEngineString::ToUpper(_AnimationName);

	if (AnimationInfos.contains(UpperAniName) == false)
	{
		MsgBoxAssert(std::string(UpperAniName) + "라는 이름의 애니메이션이 존재하지 않습니다.");
		return;
	}

	UAnimationInfo& Info = AnimationInfos[UpperAniName];
	CurAnimation = &Info;
	CurAnimation->CurFrame = 0;
	CurAnimation->CurTime = CurAnimation->Times[0];
}

void UImageRenderer::AnimationReset()
{
	CurAnimation = nullptr;
}

void UImageRenderer::Render(float _DeltaTime)
{
	if (Image == nullptr)
	{
		MsgBoxAssert("이미지가 존재하지 않는 렌더러입니다.");
	}

	if (CurAnimation != nullptr)
	{
		Image = CurAnimation->Image;
		InfoIndex = CurAnimation->Update(_DeltaTime);
	}

	FTransform RendererTrans = GetTransform();
	FTransform ActorTrans = GetOwner()->GetTransform();
	RendererTrans.AddPosition(ActorTrans.GetPosition());

	EWIndowImageType ImageType = Image->GetImageType();

	switch (ImageType)
	{
	case EWIndowImageType::IMG_BMP:
		GEngine->MainWindow.GetBackBufferImage()->TransCopy(Image, RendererTrans, InfoIndex, TransColor);
		break;
	case EWIndowImageType::IMG_PNG:
		GEngine->MainWindow.GetBackBufferImage()->AlphaCopy(Image, RendererTrans, InfoIndex, TransColor);
		break;
	default:
		MsgBoxAssert("투명처리가 불가능한 이미지 입니다.");
		break;
	}
}

void UImageRenderer::BeginPlay()
{
	USceneComponent::BeginPlay();
}