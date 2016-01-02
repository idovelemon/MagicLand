#include "MLCollisionMgr.h"
#include "../marco.h"
#include "../EntityComponent/MLComBoundBox.h"
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
			MLEntity* pEntity = *itList;
			ML_SAFE_ASSERT(pEntity != NULL, "There is an error in collision manager");
			ML_SAFE_DROP(pEntity);
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

void MLCollisionMgr::AddColEntry(MLEntity* pEntity)
{
	ML_SAFE_ASSERT(pEntity != NULL, "Please pass a valid entity pointer");
	MLEntityMainType mainType = pEntity->GetMainType();

	ML_SAFE_ASSERT(mainType <= m_ColMgrTable.size(), "Please make sure the table can hold this type of entity");
	m_ColMgrTable[mainType].push_back(pEntity);

	pEntity->Grab(); // Add the reference count
}

void MLCollisionMgr::Update(float delta)
{
	// Check collision Player with Env
	CheckColPlayerWithEnv();
}

std::vector<std::list<MLEntity*>>& MLCollisionMgr::GetColTable()
{
	return m_ColMgrTable;
}

void MLCollisionMgr::CheckColPlayerWithEnv()
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