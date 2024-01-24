#include "PlayLevel.h"

#include "Player.h"

UPlayLevel::UPlayLevel()
{

}

UPlayLevel::~UPlayLevel()
{

}

void UPlayLevel::BeginPlay()
{
	SpawnActor<Player>();

	// TODO
}