#include "MLComBoundBox.h"

#include "../marco.h"
#include "MLEntity.h"
#include "../Collision/MLCollisionMgr.h"

using namespace MagicLand;

MLComBoundBox::MLComBoundBox(MLEntity* entity, float width, float height, float px, float py)
	:MLComponent(ML_COMTYPE_BOUNDBOX, entity)
	,m_Aabb(AABB(MAKE_VECTOR2(px + width * 0.5f, py + height * 0.5f), MAKE_VECTOR2(px - width * 0.5f, py - height * 0.5f)))
	,m_IsCollided(false)
{
	m_ColEntities.clear();

	// Register the entity in collision mgr
	MLCollisionMgr::SharedInstance()->AddColEntry(entity);
}

MLComBoundBox::~MLComBoundBox()
{
	// Un-register the entity in collision mgr
	MLCollisionMgr::SharedInstance()->RemoveColEntry(m_Entity);

	for(int i = 0; i < m_ColEntities.size(); i++)
	{
		ML_SAFE_DROP(m_ColEntities[i]);
	}
	
	m_ColEntities.clear();
}

void MLComBoundBox::SetBoundBox(AABB aabb)
{
	m_Aabb = aabb;
}

AABB MLComBoundBox::GetBoundBox() const
{
	return m_Aabb;
}

void MLComBoundBox::AddEntity(MLEntity* colEntity)
{
	m_IsCollided = true;
	ML_SAFE_ASSERT(colEntity != NULL, "Can not deal with the null pointer");
	if(colEntity != NULL)
	{
		ML_SAFE_GRAB(colEntity);
		m_ColEntities.push_back(colEntity);
	}
}

bool MLComBoundBox::IsCollided() const
{
	return m_IsCollided;
}

MLColVector& MLComBoundBox::GetColEntities()
{
	return m_ColEntities;
}

void MLComBoundBox::UpdateBoundBox(VECTOR2 pos)
{
	m_Aabb.update(pos);
}

void MLComBoundBox::Reset()
{
	m_IsCollided = false;

	for(int i = 0; i < m_ColEntities.size(); i++)
	{
		ML_SAFE_DROP(m_ColEntities[i]);
	}
	
	m_ColEntities.clear();
}