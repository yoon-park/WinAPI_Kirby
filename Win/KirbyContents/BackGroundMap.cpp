#include "BackGroundMap.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore\EngineResourcesManager.h>
#include "ContentsHelper.h"

ABackGroundMap::ABackGroundMap()
{

}

ABackGroundMap::~ABackGroundMap()
{

}

void ABackGroundMap::SetMapImage(std::string_view _MapImageName)
{
	Renderer->SetImage(_MapImageName);

	UWindowImage* Image = Renderer->GetImage();
	FVector ImageScale = Image->GetScale();

	Renderer->SetTransform({ ImageScale.Half2D(), ImageScale });
}

void ABackGroundMap::SetColMapImage(std::string_view _MapImageName)
{
	ColRenderer->SetImage(_MapImageName);

	UWindowImage* Image = ColRenderer->GetImage();
	UContentsHelper::ColMapImage = Image;
	FVector ImageScale = Image->GetScale();

	ColRenderer->SetTransform({ ImageScale.Half2D(), ImageScale });
}

void ABackGroundMap::SwitchDebug()
{
	if (Renderer->IsActive() == true)
	{
		Renderer->SetActive(false);
		ColRenderer->SetActive(true);
	}
	else
	{
		Renderer->SetActive(true);
		ColRenderer->SetActive(false);
	}
}

void ABackGroundMap::BeginPlay()
{
	Renderer = CreateImageRenderer(KirbyRenderOrder::Map);
	ColRenderer = CreateImageRenderer(KirbyRenderOrder::Map);
	ColRenderer->SetActive(false);

	SetMapImage("Stage1-1.png");
	SetColMapImage("Stage1-1_Col.png");
}

void ABackGroundMap::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (EngineInput::IsDown('O'))
	{
		SwitchDebug();
	}
}