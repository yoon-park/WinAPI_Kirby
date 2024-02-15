#include "Transform.h"

#include "EngineDebug.h"

bool (*FTransform::CollisionFunction[static_cast<int>(ECollisionType::Max)][static_cast<int>(ECollisionType::Max)])(const FTransform& _Left, const FTransform& _Right);

class CollisionFunctionInit
{
public:
	CollisionFunctionInit()
	{
		FTransform::CollisionFunction[static_cast<int>(ECollisionType::CirCle)][static_cast<int>(ECollisionType::CirCle)] = FTransform::CircleToCircle;
		FTransform::CollisionFunction[static_cast<int>(ECollisionType::Rect)][static_cast<int>(ECollisionType::Rect)] = FTransform::RectToRect;
	}

	~CollisionFunctionInit()
	{

	}
};

CollisionFunctionInit Inst;

bool FTransform::CircleToCircle(const FTransform& _Left, const FTransform& _Right)
{
	FVector Dir = _Left.Position - _Right.Position;
	float Len = _Left.Scale.hX() + _Right.Scale.hX();

	return Dir.Size2D() <= Len;
}

bool FTransform::RectToRect(const FTransform& _Left, const FTransform& _Right)
{
	if (_Left.Bottom() < _Right.Top())
	{
		return false;
	}

	if (_Left.Right() < _Right.Left())
	{
		return false;
	}

	if (_Right.Bottom() < _Left.Top())
	{
		return false;
	}

	if (_Right.Right() < _Left.Left())
	{
		return false;
	}

	return true;
}

FTransform::FTransform()
{

}

FTransform::~FTransform()
{

}

bool FTransform::Collision(ECollisionType _ThisType, ECollisionType _OtherType, const FTransform& _Other)
{
	if (CollisionFunction[static_cast<int>(_ThisType)][static_cast<int>(_OtherType)] == nullptr)
	{
		MsgBoxAssert("아직 만들어지지 않은 충돌 함수를 사용했습니다.");
	}

	return CollisionFunction[static_cast<int>(_ThisType)][static_cast<int>(_OtherType)](*this, _Other);
}