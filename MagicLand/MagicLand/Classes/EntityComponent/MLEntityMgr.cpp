#include "MLEntityMgr.h"
#include "MLEntityCreator.h"
#include "../StateMachine/MLStateMachineMgr.h"
#include "../marco.h"
using namespace MagicLand;

MLEntityMgr* MLEntityMgr::s_Instance = NULL;

MLEntityMgr::MLEntityMgr()
{
	m_EntityTable.clear();
}

MLEntityMgr::~MLEntityMgr()
{
	for(MLEntityTableIt it = m_EntityTable.begin(); it != m_EntityTable.end(); ++it)
	{
		ML_SAFE_DROP(it->second);
	}

	m_EntityTable.clear();
}

MLEntityMgr* MLEntityMgr::SharedInstance()
{
	if(s_Instance == NULL)
	{
		s_Instance = new MLEntityMgr;
	}

	return s_Instance;
}

void MLEntityMgr::Destroy()
{
	ML_SAFE_DELETE(s_Instance);
}

MLEntity* MLEntityMgr::AddEntity(MLEntitySubType type, int xCoord, int yCoord, MLRoom* room)
{
	MLEntity* entity = MLEntityCreator::CreateEntity(type, xCoord, yCoord, room);
	ML_SAFE_ASSERT(entity != NULL, "Failed to create entity");

	m_EntityTable.insert(std::pair<unsigned int, MLEntity*>(entity->GetID(), entity));

	return entity;
}

MLEntity* MLEntityMgr::AddTerrianEntity(VECTOR2 min, VECTOR2 max, MLRoom* room)
{
	MLEntity* entity = MLEntityCreator::CreateTerrianEntity(min, max, room);
	ML_SAFE_ASSERT(entity != NULL, "Failed to create terrian entity");

	m_EntityTable.insert(std::pair<unsigned int, MLEntity*>(entity->GetID(), entity));

	return entity;
}

void MLEntityMgr::Update(float delta)
{
	// Run all the entity's state machine
	RunLogic();

	// Destroy all the dead entities
	DestroyAllDeadEntities();
}

void MLEntityMgr::RunLogic()
{
	for(MLEntityTableIt it = m_EntityTable.begin(); it != m_EntityTable.end(); ++it)
	{
		MLEntity* pEntity = it->second;
		ML_SAFE_ASSERT(pEntity != NULL, "There is an error in the manager");

		MLStateMachineMgr::SharedInstance()->RunStateMachine(pEntity);
	}
}

void MLEntityMgr::DestroyAllDeadEntities()
{
	for(MLEntityTableIt it = m_EntityTable.begin(); it != m_EntityTable.end();)
	{
		MLEntity* pEntity = it->second;
		ML_SAFE_ASSERT(pEntity != NULL, "There is an error in the manager");
		
		if(pEntity->IsEntityDead())
		{
			ML_SAFE_DROP(pEntity);
			it = m_EntityTable.erase(it);
		}
		else
		{
			++it;
		}
	}
}