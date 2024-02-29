#include "FadeOut.h"

#include "ContentsHelper.h"

AFadeOut::AFadeOut()
{

}

AFadeOut::~AFadeOut()
{

}

void AFadeOut::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(KirbyRenderOrder::FadeOut);
	Renderer->SetImage("FadeOut.png");
	Renderer->SetTransform({ {0,0}, {1600, 1500} });
}

void AFadeOut::Tick(float _DeltaTime)
{
	if (StartFade == false)
	{
		return;
	}

	FadeValue += _DeltaTime * Dir;
	Renderer->SetAlpha(FadeValue);
}