#include "MLComTransform.h"
using namespace MagicLand;

MLComTransform::MLComTransform(MLEntity* pEntity, float x, float y, float sx, float sy, float r)
	:MLComponent(ML_COMTYPE_TRANSFORM, pEntity)
	,m_Pos(MAKE_VECTOR2(x,y))
	,m_Scale(MAKE_VECTOR2(sx,sy))
	,m_Rot(r)
{
}

MLComTransform::~MLComTransform()
{
}

void MLComTransform::SetPos(float x, float y)
{
	m_Pos.x = x;
	m_Pos.y = y;
}

VECTOR2 MLComTransform::GetPos() const
{
	return m_Pos;
}

void MLComTransform::SetScale(float sx, float sy)
{
	m_Scale.x = sx;
	m_Scale.y = sy;
}

VECTOR2 MLComTransform::GetScale() const
{
	return m_Scale;
}

void MLComTransform::SetRot(float r)
{
	m_Rot = r;
}

float MLComTransform::GetRot() const
{
	return m_Rot;
}