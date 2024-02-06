#include "HUD.h"

#include "ContentsHelper.h"

AHUD::AHUD()
{

}

AHUD::~AHUD()
{

}

void AHUD::SetHUDImage(std::string_view _HUDImageName)
{
	Renderer->SetImage(_HUDImageName);

	UWindowImage* Image = Renderer->GetImage();
	FVector ImageScale = Image->GetScale();

	Renderer->SetTransform({ {400, 612}, ImageScale});
}

void AHUD::BeginPlay()
{
	Renderer = CreateImageRenderer(KirbyRenderOrder::HUD);

	SetHUDImage("HUD.png");
}

void AHUD::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}