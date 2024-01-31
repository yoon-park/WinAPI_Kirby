#include "TitleLogo.h"

ATitleLogo::ATitleLogo()
{

}

ATitleLogo::~ATitleLogo()
{

}

void ATitleLogo::BeginPlay()
{
	AActor::BeginPlay();

	UImageRenderer* Renderer = CreateImageRenderer();

	Renderer->SetImage("TitleLogo.bmp");
	SetActorLocation({ 400, 375 });
	Renderer->SetTransform({ {0,0}, {800, 750} });
	Renderer->SetImageCuttingTransform({ {0,0}, {256, 240} });
}

void ATitleLogo::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}