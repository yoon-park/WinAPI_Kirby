#include "Fire.h"

AFire::AFire()
{

}

AFire::~AFire()
{

}

void AFire::BeginPlay()
{
	{
		AActor::BeginPlay();

		UImageRenderer* Renderer = CreateImageRenderer(-10);

		Renderer->SetImage("Fire.bmp");
		Renderer->SetImageCuttingTransform({ {0,0}, {16, 16} });
		Renderer->SetTransform({ {0,0}, {50, 50} });
	}

	Destroy(2.0f);
}

void AFire::Tick(float _DeltaTime)
{
	AddActorLocation(Dir * Speed * _DeltaTime);
}