#include "ml_entity.h"

#include "marco.h"
#include "ml_component.h"
#include "ml_system.h"

using namespace magicland;

unsigned int MLEntity::s_IDGenerator = 0;

MLEntity::MLEntity(MLEntityMainType main, MLEntitySubType sub)
	:m_System(NULL)
  ,m_IsEntityDead(false)
	,m_ID(s_IDGenerator++)
	,m_MainType(main)
	,m_SubType(sub) {
	ML_SAFE_ASSERT(ML_ETYMAINTYPE_NONE < main && main < ML_ETYMAINTYPE_TOTAL, "Please pass the right main type");
	ML_SAFE_ASSERT(ML_ETYSUBTYPE_NONE < sub && sub < ML_ETYSUBTYPE_TOTAL, "Please pass the right sub type");
	m_ComponentTable.clear();
}

MLEntity::~MLEntity() {
  Release();
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

void MLEntity::AttachSystem(MLSystem* system) {

  ML_SAFE_ASSERT(system != NULL, "Null Pointer Error");
  if(system != NULL) {
    ML_SAFE_DROP(m_System);
    m_System = system;
    ML_SAFE_GRAB(m_System);
  }
}

void MLEntity::DeattachSystem() {

  ML_SAFE_DROP(m_System);
  m_System = NULL;
}

void MLEntity::Run(float delta) {
  
  // Run the system
  ML_SAFE_ASSERT(m_System != NULL, "Null Pointer Error");
  if(m_System != NULL) {
    m_System->Run(delta);
  }

  // Run the components
  for (MLComponentTableIt it = m_ComponentTable.begin(); it != m_ComponentTable.end(); ++it) {
		MLComponent* component = it->second;
    ML_SAFE_ASSERT(component != NULL, "Null Pointer Error");
    if(component != NULL) {
      component->Run(delta);
    }
	}
}

void MLEntity::Release() {

  RemoveAllComponents();

  DeattachSystem();
}