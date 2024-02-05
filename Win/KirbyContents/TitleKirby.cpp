#include "TitleKirby.h"

#include "ContentsHelper.h"

ATitleKirby::ATitleKirby()
{

}

ATitleKirby::~ATitleKirby()
{

}

void ATitleKirby::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(KirbyRenderOrder::Player);
	Renderer->SetImage("TitleKirby.png");
	Renderer->SetImageCuttingTransform({ {0,0}, {64, 64} });
	Renderer->SetTransform({ {0,0}, {200, 200} });

	Renderer->CreateAnimation("Idle", "TitleKirby.png", 0, 11, 0.1f, true);
	Renderer->ChangeAnimation("Idle");
}

void ATitleKirby::Tick(float _DeltaTime)
{

}