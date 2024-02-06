#pragma once
#include <EngineBase\EngineMath.h>
#include <EngineCore\EngineCore.h>
#include <EngineCore\ImageRenderer.h>

enum KirbyRenderOrder
{
	HUD,
	Map,
	Player
};

enum class EActorDir
{
	Left,
	Right,
};

enum class EPlayState
{
	None,
	CameraFreeMove,
	FreeMove,
	Idle,
	Move,
	Jump,
};

class UContentsHelper
{
public:
	static UWindowImage* ColMapImage;

private:
	UContentsHelper();
	~UContentsHelper();
};