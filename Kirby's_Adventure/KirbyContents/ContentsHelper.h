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
	Ability,
	FadeOut,
};

enum class KirbyCollisionOrder
{
	Monster,
	PlayerAbsorb,
	PlayerAbility,
	Player,
};

enum class EActorDir
{
	Left,
	Right,
	Up,
	Down
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
	Absorb,
	Digest,
	Spit,
	Door,
};

enum class EMonsterState
{
	None,
	Move,
	Attack,
	Absorb,
};

enum class EAbiltyType
{
	None,
	Spark,
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