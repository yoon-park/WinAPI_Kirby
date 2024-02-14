#include "Transform.h"

FTransform::FTransform()
{

}

FTransform::~FTransform()
{

}

bool FTransform::Collision(ECollisionType _ThisType, ECollisionType _OtherType, const FTransform& _Other)
{
	switch (_ThisType)
	{
	case Point:
		break;
	case CirCle:
		break;
	case Rect:
		break;
	default:
		break;
	}

	return false;
}