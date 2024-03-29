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
	ImageScale = Image->GetScale();

	Renderer->SetTransform({ ImageScale.Half2D(), ImageScale });
}

void ABackGroundMap::SetColMapImage(std::string_view _MapImageName)
{
	ColRenderer->SetImage(_MapImageName);

	UWindowImage* Image = ColRenderer->GetImage();
	UContentsHelper::ColMapImage = Image;
	ImageScale = Image->GetScale();

	ColRenderer->SetTransform({ ImageScale.Half2D(), ImageScale });
}

void ABackGroundMap::SwitchDebug()
{
	if (Renderer->IsActive() == true)
	{
		Renderer->ActiveOff();
		ColRenderer->ActiveOn();
	}
	else
	{
		Renderer->ActiveOn();
		ColRenderer->ActiveOff();
	}
}

void ABackGroundMap::BeginPlay()
{
	Renderer = CreateImageRenderer(KirbyRenderOrder::Map);
	ColRenderer = CreateImageRenderer(KirbyRenderOrder::Map);
	ColRenderer->ActiveOff();
}

void ABackGroundMap::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (UEngineInput::IsDown('O'))
	{
		SwitchDebug();
	}
}