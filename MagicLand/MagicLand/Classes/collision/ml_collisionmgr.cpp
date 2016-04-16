#include "ml_collisionmgr.h"

#include "marco.h"
#include "entitycomponent/ml_com_boundbox.h"
#include "entitycomponent/ml_com_state.h"
#include "entitycomponent/ml_entity.h"

using namespace magicland;

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
	if(entity != NULL)
	{
		MLEntityMainType mainType = entity->GetMainType();

		ML_SAFE_ASSERT(mainType <= m_ColMgrTable.size(), "Please make sure the table can hold this type of entity");
		if(mainType <= m_ColMgrTable.size())
		{
			m_ColMgrTable[mainType].push_back(entity);
		}

		ML_SAFE_GRAB(entity); // Add the reference count
	}
}

void MLCollisionMgr::RemoveColEntry(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Please pass a valid entity pointer");
	if(entity != NULL)
	{
		MLEntityMainType mainType = entity->GetMainType();

		ML_SAFE_ASSERT(mainType <= m_ColMgrTable.size(), "Please make sure the table has the collision entry of this type entity");
		if(mainType <= m_ColMgrTable.size())
		{
			bool bFound = false;
			for(MLColMgrList::iterator it = m_ColMgrTable[mainType].begin(); it != m_ColMgrTable[mainType].end(); ++it)
			{
				MLEntity* colEntry = *it;
				ML_SAFE_ASSERT(colEntry != NULL, "There is an error");
				if(colEntry != NULL)
				{
					if(colEntry->GetID() == entity->GetID())
					{
						ML_SAFE_DROP(entity);
						m_ColMgrTable[mainType].erase(it);
						bFound = true;
						break;
					}
				}
			}

			ML_SAFE_ASSERT(bFound == true, "Can not find the collision entry of this entity");
		}
	}
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

	// Detect the collision between player's magic and enemy
	DetectColEnemyWithMagic();

	// Detect the collision between enemy and environment
	DetectColEnemyWithEnv();

	// Detect the collision between enemy's magic and env
	DetectColEnemyMagicWithEnv();
}

void MLCollisionMgr::CollisionResponse()
{
	for(int i = 0; i < m_ColMgrTable.size(); i++)
	{
		for(MLColMgrListIt it = m_ColMgrTable[i].begin(); it != m_ColMgrTable[i].end(); ++it)
		{
			MLEntity* entity = *it;
			ML_SAFE_ASSERT(entity != NULL, "There is an error");
			if(entity != NULL)
			{
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
}

void MLCollisionMgr::ClearCollisionInfo()
{
	for(int i = 0; i < m_ColMgrTable.size(); i++)
	{
		for(MLColMgrListIt it = m_ColMgrTable[i].begin(); it != m_ColMgrTable[i].end(); ++it)
		{
			MLEntity* entity = *it;
			ML_SAFE_ASSERT(entity != NULL, "There is an error");
			if(entity != NULL)
			{
				MLComBoundBox* pBox = (MLComBoundBox*)entity->GetComponent(ML_COMTYPE_BOUNDBOX);
				ML_SAFE_ASSERT(pBox != NULL, "There is an error");
				if(pBox != NULL)
				{
					pBox->Reset();
				}
			}
		}
	}
}

void MLCollisionMgr::DetectColPlayerWithEnv()
{
	for(MLColMgrListIt itPlayer = m_ColMgrTable[ML_ETYMAINTYPE_PLAYER].begin(); itPlayer != m_ColMgrTable[ML_ETYMAINTYPE_PLAYER].end(); ++itPlayer)
	{
		MLEntity* pPlayer = *itPlayer;
		ML_SAFE_ASSERT(pPlayer != NULL, "There is an error");
		if(pPlayer != NULL)
		{
			MLComBoundBox* playerBox = (MLComBoundBox*)pPlayer->GetComponent(ML_COMTYPE_BOUNDBOX);
			ML_SAFE_ASSERT(playerBox != NULL, "The entity don't have the entity");
			if(playerBox != NULL)
			{
				for(MLColMgrListIt itEnv = m_ColMgrTable[ML_ETYMAINTYPE_ENV].begin(); itEnv != m_ColMgrTable[ML_ETYMAINTYPE_ENV].end(); ++itEnv)
				{
					MLEntity* pEnv = *itEnv;
					ML_SAFE_ASSERT(pEnv != NULL, "There is an error");
					if(pEnv != NULL)
					{
						MLComBoundBox* envBox = (MLComBoundBox*)pEnv->GetComponent(ML_COMTYPE_BOUNDBOX);
						ML_SAFE_ASSERT(envBox != NULL, "The entity don't have the entity");
						if(envBox != NULL)
						{
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
			}
		}
	}
}

void MLCollisionMgr::DetectColEnemyWithMagic()
{
	for(MLColMgrListIt itEnemy = m_ColMgrTable[ML_ETYMAINTYPE_ENEMY].begin(); itEnemy != m_ColMgrTable[ML_ETYMAINTYPE_ENEMY].end(); ++itEnemy)
	{
		MLEntity* pEnemy = *itEnemy;
		ML_SAFE_ASSERT(pEnemy != NULL, "There is an error");
		if(pEnemy != NULL)
		{
			MLComBoundBox* enemyBox = (MLComBoundBox*)pEnemy->GetComponent(ML_COMTYPE_BOUNDBOX);
			ML_SAFE_ASSERT(enemyBox != NULL, "The entity don't have the entity");
			if(enemyBox != NULL)
			{
				for(MLColMgrListIt itMagic = m_ColMgrTable[ML_ETYMAINTYPE_PLAYER_MAGIC].begin(); itMagic != m_ColMgrTable[ML_ETYMAINTYPE_PLAYER_MAGIC].end(); ++itMagic)
				{
					MLEntity* pMagic = *itMagic;
					ML_SAFE_ASSERT(pMagic != NULL, "There is an error");
					
					MLComBoundBox* magicBox = (MLComBoundBox*)pMagic->GetComponent(ML_COMTYPE_BOUNDBOX);
					ML_SAFE_ASSERT(magicBox != NULL, "The entity don't have the entity");

					if(pMagic != NULL && magicBox != NULL)
					{
						// Check collision with the two bounding box
						if(magicBox->GetBoundBox().intersectWithAABB(enemyBox->GetBoundBox()))
						{
							// Pass the collision information
							magicBox->AddEntity(pEnemy);
							enemyBox->AddEntity(pMagic);
						}
					}
				}
			}
		}
	}
}

void MLCollisionMgr::DetectColEnemyWithEnv()
{
	for(MLColMgrListIt itEnemy = m_ColMgrTable[ML_ETYMAINTYPE_ENEMY].begin(); itEnemy != m_ColMgrTable[ML_ETYMAINTYPE_ENEMY].end(); ++itEnemy)
	{
		MLEntity* pEnemy = *itEnemy;
		ML_SAFE_ASSERT(pEnemy != NULL, "There is an error");

		MLComBoundBox* enemyBox = (MLComBoundBox*)pEnemy->GetComponent(ML_COMTYPE_BOUNDBOX);
		ML_SAFE_ASSERT(enemyBox != NULL, "The entity don't have the entity");

		if(pEnemy != NULL && enemyBox != NULL)
		{
			for(MLColMgrListIt itEnv = m_ColMgrTable[ML_ETYMAINTYPE_ENV].begin(); itEnv != m_ColMgrTable[ML_ETYMAINTYPE_ENV].end(); ++itEnv)
			{
				MLEntity* pEnv = *itEnv;
				ML_SAFE_ASSERT(pEnv != NULL, "There is an error");

				MLComBoundBox* envBox = (MLComBoundBox*)pEnv->GetComponent(ML_COMTYPE_BOUNDBOX);
				ML_SAFE_ASSERT(envBox != NULL, "The entity don't have the entity");

				if(pEnv != NULL && envBox != NULL)
				{
					// Check collision with the two bounding box
					if(envBox->GetBoundBox().intersectWithAABB(enemyBox->GetBoundBox()))
					{
						// Pass the collision information
						envBox->AddEntity(pEnemy);
						enemyBox->AddEntity(pEnv);
					}
				}
			}
		}
	}
}

void MLCollisionMgr::DetectColEnemyMagicWithEnv()
{
	for(MLColMgrListIt itEnemyMagic = m_ColMgrTable[ML_ETYMAINTYPE_ENEMYMAGIC].begin(); itEnemyMagic != m_ColMgrTable[ML_ETYMAINTYPE_ENEMYMAGIC].end(); ++itEnemyMagic)
	{
		MLEntity* pEnemyMagic = *itEnemyMagic;
		ML_SAFE_ASSERT(pEnemyMagic != NULL, "There is an error");

		MLComBoundBox* enemyMagicBox = (MLComBoundBox*)pEnemyMagic->GetComponent(ML_COMTYPE_BOUNDBOX);
		ML_SAFE_ASSERT(enemyMagicBox != NULL, "The entity don't have the entity");

		if(pEnemyMagic != NULL && enemyMagicBox != NULL)
		{
			for(MLColMgrListIt itEnv = m_ColMgrTable[ML_ETYMAINTYPE_ENV].begin(); itEnv != m_ColMgrTable[ML_ETYMAINTYPE_ENV].end(); ++itEnv)
			{
				MLEntity* pEnv = *itEnv;
				ML_SAFE_ASSERT(pEnv != NULL, "There is an error");

				MLComBoundBox* envBox = (MLComBoundBox*)pEnv->GetComponent(ML_COMTYPE_BOUNDBOX);
				ML_SAFE_ASSERT(envBox != NULL, "The entity don't have the entity");

				if(pEnv != NULL && envBox != NULL)
				{
					// Check collision with the two bounding box
					if(envBox->GetBoundBox().intersectWithAABB(enemyMagicBox->GetBoundBox()))
					{
						// Pass the collision information
						envBox->AddEntity(pEnemyMagic);
						enemyMagicBox->AddEntity(pEnv);
					}
				}
			}
		}
	}
}