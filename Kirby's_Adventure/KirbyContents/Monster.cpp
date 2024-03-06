#include "Monster.h"

#include "Player.h"

AMonster::AMonster()
{

}

AMonster::~AMonster()
{

}

void AMonster::BeginPlay()
{
	AActor::BeginPlay();
}

void AMonster::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}