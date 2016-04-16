#include "MLComMovement.h"

using namespace MagicLand;

MLComMovement::MLComMovement(MLEntity* entity)
	:MLComponent(ML_COMTYPE_MOVEMENT, entity)
	,m_Vel(MAKE_VECTOR2(0.0f, 0.0f))
	,m_Gravity(0.0f)
	,m_MaxFallSpeed(0.0f)
{
}

MLComMovement::~MLComMovement()
{
}

void MLComMovement::SetVel(float vx, float vy)
{
	m_Vel.x = vx;
	m_Vel.y = vy;
}

VECTOR2 MLComMovement::GetVel() const
{
	return m_Vel;
}

void MLComMovement::SetGravity(float g)
{
	m_Gravity = g;
}

float MLComMovement::GetGravity() const
{
	return m_Gravity;
}

void MLComMovement::SetMaxFallSpeed(float max)
{
	m_MaxFallSpeed = max;
}

float MLComMovement::GetMaxFallSpeed() const
{
	return m_MaxFallSpeed;
}