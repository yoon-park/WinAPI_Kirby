#pragma once
#include <EngineBase\EngineMath.h>
#include <EngineCore\EngineCore.h>
#include <EngineCore\ImageRenderer.h>

enum class KirbyRenderOrder
{
	Map,
	HUD,
	Effect,
	Monster,
	Player,
	Ability,
	FadeOut,
};

enum class KirbyCollisionOrder
{
	None,
	Monster,
	MonsterAbilty,
	PlayerAbsorb,
	PlayerAbility,
	Player,
	Detect
};

enum class EActorDir
{
	Left,
	Right,
	Up,
	Down
};

enum class EActorType
{
	None,
	Player,
	Monster,
	Ability,
	Effect,
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
	Slide,
	Squeeze,
	Fly,
	SpitFly,
	Absorb,
	Digest,
	Spit,
	Attack,
	Door,
};

enum class EMonsterState
{
	None,
	Idle,
	Move,
	Jump,
	Breakfall,
	Fall,
	Attack,
	Absorb,
};

enum class EAbiltyType
{
	None,
	Beam,
	Spark,
	Fire,
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