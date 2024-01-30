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
		UImageRenderer* Renderer = CreateImageRenderer(-10);
		Renderer->SetImageToScale("Fire.bmp");
	}

	Destroy(2.0f);
}

void AFire::Tick(float _DeltaTime)
{
	AddActorLocation(Dir * Speed * _DeltaTime);
}