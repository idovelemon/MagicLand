#include "MLEntityMgr.h"
#include "MLEntityCreator.h"
#include "../StateMachine/MLStateMachineMgr.h"
#include "../marco.h"
using namespace MagicLand;

MLEntityMgr* MLEntityMgr::s_Instance = NULL;

MLEntityMgr::MLEntityMgr()
	:m_Player(NULL)
{
	m_EntityTable.clear();
}

MLEntityMgr::~MLEntityMgr()
{
	for(MLEntityTableIt it = m_EntityTable.begin(); it != m_EntityTable.end(); ++it)
	{
		ML_SAFE_RELEASE_ENTITY(it->second);
	}

	m_EntityTable.clear();

	ML_SAFE_DROP(m_Player);
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

void MLEntityMgr::AddEntity(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Can not add empty entity");
	m_EntityTable.insert(std::pair<unsigned int, MLEntity*>(entity->GetID(), entity));

	// Cache Player's entity
	if(ML_ETYMAINTYPE_PLAYER == entity->GetMainType())
	{
		ML_SAFE_DROP(m_Player);
		m_Player = entity;
		ML_SAFE_GRAB(m_Player);
	}
}

void MLEntityMgr::Update(float delta)
{
	// Run all the entity's state machine
	RunLogic();

	// Destroy all the dead entities
	DestroyAllDeadEntities();
}

MLEntity* MLEntityMgr::GetPlayer()
{
	return m_Player;
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
			ML_SAFE_RELEASE_ENTITY(pEntity);
			it = m_EntityTable.erase(it);
		}
		else
		{
			++it;
		}
	}
}