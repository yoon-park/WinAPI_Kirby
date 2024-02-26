#pragma once
#include <EngineBase\EngineMath.h>
#include <EngineCore\EngineCore.h>
#include <EngineCore\ImageRenderer.h>

enum class KirbyRenderOrder
{
	Map,
	HUD,
	Monster,
	Player,
};

enum class KirbyCollisionOrder
{
	PlayerAbility,
	Monster,
	Player,
};

enum class EActorDir
{
	Left,
	Right
};

enum class EPlayState
{
	None,
	CameraFreeMove,
	FreeMove,
	Idle,
	Run,
	Dash,
	Break,
	Jump,
	Breakfall,
	Fall,
	Crouch,
	Squeeze,
	Fly,
	SpitFly,
};

enum class EGroundType
{
	None,
	Flat,
	SlopeUp,
	SlopeDown,
	ScarpUp,
	ScarpDown
};

class UContentsHelper
{
public:
	static UWindowImage* ColMapImage;

private:
	UContentsHelper();
	~UContentsHelper();
};