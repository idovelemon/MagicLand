#include "entitycomponent/ml_entity.h"

#include "marco.h"
#include "entitycomponent/ml_component.h"
#include "round/ml_room.h"

using namespace magicland;

unsigned int MLEntity::s_IDGenerator = 0;

MLEntity::MLEntity(MLEntityMainType main, MLEntitySubType sub, MLRoom* room)
	:m_IsEntityDead(false)
	,m_ID(s_IDGenerator++)
	,m_MainType(main)
	,m_SubType(sub)
	,m_Room(room) {
	ML_SAFE_ASSERT(ML_ETYMAINTYPE_NONE < main && main < ML_ETYMAINTYPE_TOTAL, "Please pass the right main type");
	ML_SAFE_ASSERT(ML_ETYSUBTYPE_NONE < sub && sub < ML_ETYSUBTYPE_TOTAL, "Please pass the right sub type");
	ML_SAFE_ASSERT(room != NULL, "Please pass a valid room pointer");
	m_ComponentTable.clear();
}

MLEntity::~MLEntity() {
	for (MLComponentTableIt it = m_ComponentTable.begin(); it != m_ComponentTable.end(); ++it) {
		ML_SAFE_DELETE(it->second);
	}

	m_ComponentTable.clear();
}

void MLEntity::AddComponent(MLComponent* com) {
	ML_SAFE_ASSERT(com != NULL, "Please make sure the com is not null");

	MLComType type = com->GetType();

	if (m_ComponentTable.find(type) != m_ComponentTable.end()) {
		ML_SAFE_ASSERT(false, "Don't add one type component twice");
	}
	
	m_ComponentTable.insert(std::pair<MLComType, MLComponent*>(type, com));
	ML_SAFE_GRAB(com);
}

void MLEntity::RemoveAllComponents() {
	for (MLComponentTableIt it = m_ComponentTable.begin(); it != m_ComponentTable.end(); ++it) {
		ML_SAFE_DROP(it->second);
	}

	m_ComponentTable.clear();
}

MLComponent* MLEntity::GetComponent(MLComType type) {
	ML_SAFE_ASSERT(type > ML_COMTYPE_NONE && type < ML_COMTYPE_TOTAL, "Please pass the correct component type");

	MLComponent* result = NULL;
	
	if(m_ComponentTable.size() > 0) {
		MLComponentTableIt it = m_ComponentTable.find(type);
		
    if( it != m_ComponentTable.end()) {
			result = it->second;
		}
	}
	
	return result;
}

bool MLEntity::IsEntityDead() {
	return m_IsEntityDead;
}

void MLEntity::KillEntity() {
	m_IsEntityDead = true;
}

unsigned int MLEntity::GetID() const {
	return m_ID;
}

MLEntityMainType MLEntity::GetMainType() const {
	return m_MainType;
}

MLEntitySubType MLEntity::GetSubType() const {
	return m_SubType;
}

MLRoom* MLEntity::GetRoom() const {
	return m_Room;
}