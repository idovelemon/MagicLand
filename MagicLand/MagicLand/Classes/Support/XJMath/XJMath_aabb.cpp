#include"XJMath.h"

AABB::AABB(VECTOR2 max, VECTOR2 min)
	:m_vMax(max),
	m_vMin(min)
{

}

bool AABB::intersectWithAABB(const AABB& aabb)
{
	if(aabb.m_vMax.x < m_vMin.x)	return false ;
	if(aabb.m_vMax.y < m_vMin.y)	return false ;
	if(aabb.m_vMin.x > m_vMax.x)	return false ;
	if(aabb.m_vMin.y > m_vMax.y)	return false ;
	return true ;
}// end for intersectWithAABB

float AABB::getWidth() const
{
	return m_vMax.x - m_vMin.x ;
}// end for getWidth

float AABB::getHeight() const
{
	return m_vMax.y - m_vMin.y ;
}// end for getHeight

void AABB::update(VECTOR2 center)
{
	float width = m_vMax.x - m_vMin.x ;
	float height = m_vMax.y - m_vMin.y ;
	m_vMax = MAKE_VECTOR2(center.x + width/2,
		center.y + height/2);
	m_vMin = MAKE_VECTOR2(center.x - width/2,
		center.y - height/2);
}// end for update