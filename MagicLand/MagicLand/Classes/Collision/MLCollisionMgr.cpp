#include "MLCollisionMgr.h"
#include "../marco.h"
#include "../EntityComponent/MLComBoundBox.h"
#include "../EntityComponent/MLComState.h"
using namespace MagicLand;

MLCollisionMgr* MLCollisionMgr::s_Instance = NULL;

MLCollisionMgr::MLCollisionMgr()
{
	m_ColMgrTable.clear();
	m_ColMgrTable.resize(ML_ETYMAINTYPE_TOTAL, MLColMgrList());
}

MLCollisionMgr::~MLCollisionMgr()
{
	for(MLColMgrTableIt itTable = m_ColMgrTable.begin(); itTable != m_ColMgrTable.end(); ++itTable)
	{
		MLColMgrList colList = *itTable;

		for(MLColMgrListIt itList = colList.begin(); itList != colList.end(); ++itList)
		{
			MLEntity* entity = *itList;
			ML_SAFE_ASSERT(entity != NULL, "There is an error in collision manager");
			ML_SAFE_DROP(entity);
		}

		colList.clear();
	}

	m_ColMgrTable.clear();
}

MLCollisionMgr* MLCollisionMgr::SharedInstance()
{
	if(s_Instance == NULL)
	{
		s_Instance = new MLCollisionMgr();
		ML_SAFE_ASSERT(s_Instance != NULL, "Create the collision manager error");
	}

	return s_Instance;
}

void MLCollisionMgr::Destroy()
{
	ML_SAFE_DELETE(s_Instance);
}

void MLCollisionMgr::AddColEntry(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Please pass a valid entity pointer");
	MLEntityMainType mainType = entity->GetMainType();

	ML_SAFE_ASSERT(mainType <= m_ColMgrTable.size(), "Please make sure the table can hold this type of entity");
	m_ColMgrTable[mainType].push_back(entity);

	ML_SAFE_GRAB(entity); // Add the reference count
}

void MLCollisionMgr::RemoveColEntry(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Please pass a valid entity pointer");
	MLEntityMainType mainType = entity->GetMainType();

	ML_SAFE_ASSERT(mainType <= m_ColMgrTable.size(), "Please make sure the table has the collision entry of this type entity");

	bool bFound = false;
	for(MLColMgrList::iterator it = m_ColMgrTable[mainType].begin(); it != m_ColMgrTable[mainType].end(); ++it)
	{
		MLEntity* colEntry = *it;
		ML_SAFE_ASSERT(colEntry != NULL, "There is an error");

		if(colEntry->GetID() == entity->GetID())
		{
			ML_SAFE_DROP(entity);
			m_ColMgrTable[mainType].erase(it);
			bFound = true;
			break;
		}
	}

	ML_SAFE_ASSERT(bFound == true, "Can not find the collision entry of this entity");
}

void MLCollisionMgr::Update(float delta)
{
	// Collision Detect
	CollisionDetect();

	// Collision Response
	CollisionResponse();
}

std::vector<std::list<MLEntity*>>& MLCollisionMgr::GetColTable()
{
	return m_ColMgrTable;
}

unsigned int MLCollisionMgr::GetCVNum()
{
	unsigned int cvNum = 0;
	for(int i = 0;i < m_ColMgrTable.size(); i++)
	{
		cvNum += m_ColMgrTable[i].size();
	}

	return cvNum;
}

void MLCollisionMgr::CollisionDetect()
{
	// Clear the collided information of last frame
	ClearCollisionInfo();

	// Detect the collision between player and environment
	DetectColPlayerWithEnv();
}

void MLCollisionMgr::CollisionResponse()
{
	for(int i = 0; i < m_ColMgrTable.size(); i++)
	{
		for(MLColMgrListIt it = m_ColMgrTable[i].begin(); it != m_ColMgrTable[i].end(); ++it)
		{
			MLEntity* entity = *it;
			ML_SAFE_ASSERT(entity != NULL, "There is an error");

			MLComState* pState = (MLComState*)entity->GetComponent(ML_COMTYPE_STATE);
			
			// If this entity has state component
			// That means the entity has the state machine to handle the collision response
			if(pState != NULL)
			{
				pState->GetState()->OnCollision(entity);
			}
		}
	}
}

void MLCollisionMgr::ClearCollisionInfo()
{
	for(int i = 0; i < m_ColMgrTable.size(); i++)
	{
		for(MLColMgrListIt it = m_ColMgrTable[i].begin(); it != m_ColMgrTable[i].end(); ++it)
		{
			MLEntity* entity = *it;
			ML_SAFE_ASSERT(entity != NULL, "There is an error");

			MLComBoundBox* pBox = (MLComBoundBox*)entity->GetComponent(ML_COMTYPE_BOUNDBOX);
			ML_SAFE_ASSERT(pBox != NULL, "There is an error");
			pBox->Reset();
		}
	}
}

void MLCollisionMgr::DetectColPlayerWithEnv()
{
	for(MLColMgrListIt itPlayer = m_ColMgrTable[ML_ETYMAINTYPE_PLAYER].begin(); itPlayer != m_ColMgrTable[ML_ETYMAINTYPE_PLAYER].end(); ++itPlayer)
	{
		MLEntity* pPlayer = *itPlayer;
		ML_SAFE_ASSERT(pPlayer != NULL, "There is an error");

		MLComBoundBox* playerBox = (MLComBoundBox*)pPlayer->GetComponent(ML_COMTYPE_BOUNDBOX);
		ML_SAFE_ASSERT(playerBox != NULL, "The entity don't have the entity");

		for(MLColMgrListIt itEnv = m_ColMgrTable[ML_ETYMAINTYPE_ENV].begin(); itEnv != m_ColMgrTable[ML_ETYMAINTYPE_ENV].end(); ++itEnv)
		{
			MLEntity* pEnv = *itEnv;
			ML_SAFE_ASSERT(pEnv != NULL, "There is an error");

			MLComBoundBox* envBox = (MLComBoundBox*)pEnv->GetComponent(ML_COMTYPE_BOUNDBOX);
			ML_SAFE_ASSERT(envBox != NULL, "The entity don't have the entity");

			// Check collision with the two bounding box
			if(envBox->GetBoundBox().intersectWithAABB(playerBox->GetBoundBox()))
			{
				// Pass the collision information
				envBox->AddEntity(pPlayer);
				playerBox->AddEntity(pEnv);
			}
		}
	}
}