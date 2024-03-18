#include "TheEnd.h"

ATheEnd::ATheEnd()
{

}

ATheEnd::~ATheEnd()
{

}

void ATheEnd::BeginPlay()
{
	Renderer = CreateImageRenderer(KirbyRenderOrder::Ability);
	Renderer->SetImage("Item_Right.png", 1);
	Renderer->SetTransform({ {0,0}, {300, 300} });
}

void ATheEnd::Tick(float _DeltaTime)
{

}