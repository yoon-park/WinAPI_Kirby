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

	Renderer->SetImage("TitleLogo.png");
	SetActorLocation({ 400, 350 });
	Renderer->SetImageCuttingTransform({ {0,0}, {256, 240} });
	Renderer->SetTransform({ {0,0}, {800, 750} });
}

void ATitleLogo::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}