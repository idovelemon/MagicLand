#include "MLComOrgeWalkRange.h"
using namespace MagicLand;

MLComOrgeWalkRange::MLComOrgeWalkRange(MLEntity* entity, float centerX, float width)
	:MLComponent(ML_COMTYPE_ORGE_WALKRANGE, entity)
	,m_CenterPosX(centerX)
	,m_Width(width)
{
}

MLComOrgeWalkRange::~MLComOrgeWalkRange()
{
}

float MLComOrgeWalkRange::GetCenterX()
{
	return m_CenterPosX;
}

float MLComOrgeWalkRange::GetWidth()
{
	return m_Width;
}