#include "Kirby112.h"

AKirby112::AKirby112()
{
	
}

AKirby112::~AKirby112()
{

}

void AKirby112::BeginPlay()
{
	APlayer::BeginPlay();

	StateChange(EPlayState::Idle);
}

void AKirby112::Tick(float _DeltaTime)
{
	APlayer::Tick(_DeltaTime);
}

void AKirby112::IntoDoor()
{

}