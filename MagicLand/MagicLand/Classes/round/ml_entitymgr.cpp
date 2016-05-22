#include "ml_entitymgr.h"

#include <list>

#include "marco.h"
#include "ecs/ml_entity.h"

namespace magicland {

//-------------------------------------------------------------------------------
// Class/Typedef
//-------------------------------------------------------------------------------
class MLEntityMgrImp{
public:
  static MLEntityMgrImp* SharedInstance();
  static void DestroyInstance();

public:
  int32_t Init();
  void Update(float delta);
  void Destroy();

  void AddEntity(MLEntity* entity);
  void ClearAllEntity();

protected:
  MLEntityMgrImp();
  virtual ~MLEntityMgrImp();

private:
  std::list<MLEntity*>  m_Entitys;

  static MLEntityMgrImp* s_Instance;
  ML_DISALLOW_COPY_AND_ASSIGN(MLEntityMgrImp);
};

//--------------------------------------------------------------------------
// Implement
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// Implement MLEntityMgrImp
//--------------------------------------------------------------------------
MLEntityMgrImp* MLEntityMgrImp::s_Instance = NULL;

MLEntityMgrImp::MLEntityMgrImp() {
  m_Entitys.clear();
}

MLEntityMgrImp::~MLEntityMgrImp() {
  Destroy();
}

MLEntityMgrImp* MLEntityMgrImp::SharedInstance() {
  if(s_Instance == NULL) {
    s_Instance = new MLEntityMgrImp();
    ML_SAFE_ASSERT(s_Instance != NULL, "Null Pointer Error");
  }

  return s_Instance;
}

void MLEntityMgrImp::DestroyInstance() {
  ML_SAFE_DELETE(s_Instance);
}

int32_t MLEntityMgrImp::Init() {
  int32_t result = 0;
  return result;
}

void MLEntityMgrImp::Update(float delta) {
  // Run all entity
  std::list<MLEntity*>::iterator it = m_Entitys.begin();
  for(; it != m_Entitys.end(); ++it) {
    MLEntity* entity = *it;
    ML_SAFE_ASSERT(entity != NULL, "Null Pointer Error");
    if(entity != NULL) {
      entity->Run(delta);
    }
  }

  // Destroy dead entity
  it = m_Entitys.begin();
  for(; it != m_Entitys.end();) {
    MLEntity* entity = *it;
    ML_SAFE_ASSERT(entity != NULL, "Null Pointer Error");
    if(entity != NULL) {
      if(entity->IsEntityDead()) {
        entity->Release();
        ML_SAFE_DROP(entity);
        std::list<MLEntity*>::iterator temp = it;
        ++it;
        m_Entitys.erase(temp);
      } else {
        ++it;
      }
    } else {
      ++it;
    }
  }
}

void MLEntityMgrImp::Destroy() {
  ClearAllEntity();
}

void MLEntityMgrImp::AddEntity(MLEntity* entity) {
  ML_SAFE_ASSERT(entity != NULL, "Null Pointer Error");
  m_Entitys.push_back(entity);
  ML_SAFE_GRAB(entity);
}

void MLEntityMgrImp::ClearAllEntity() {
  std::list<MLEntity*>::iterator it = m_Entitys.begin();
  for(; it != m_Entitys.end(); ++it) {
    MLEntity* entity = *it;
    entity->Release();
    ML_SAFE_DROP(entity);
  }

  m_Entitys.clear();  
}

//--------------------------------------------------------------------------
// Implement MLEntityMgr
//--------------------------------------------------------------------------
int32_t MLEntityMgr::Init() {
  int32_t result = -1;

  MLEntityMgrImp* instance = MLEntityMgrImp::SharedInstance();
  ML_SAFE_ASSERT(instance != NULL, "Null Pointer Error");
  if(instance != NULL) {
    result = instance->Init();
  }

  return result;
}

void MLEntityMgr::Update(float delta) {
  MLEntityMgrImp* instance = MLEntityMgrImp::SharedInstance();
  ML_SAFE_ASSERT(instance != NULL, "Null Pointer Error");
  if(instance != NULL) {
    instance->Update(delta);
  }
}

void MLEntityMgr::Destroy() {
  MLEntityMgrImp* instance = MLEntityMgrImp::SharedInstance();
  ML_SAFE_ASSERT(instance != NULL, "Null Pointer Error");
  if(instance != NULL) {
    instance->Destroy();
    MLEntityMgrImp::DestroyInstance();
  }
}

void MLEntityMgr::AddEntity(MLEntity* entity) {
  MLEntityMgrImp* instance = MLEntityMgrImp::SharedInstance();
  ML_SAFE_ASSERT(instance != NULL, "Null Pointer Error");
  if(instance != NULL) {
    instance->AddEntity(entity);
  }
}

void MLEntityMgr::ClearAllEntity() {
  MLEntityMgrImp* instance = MLEntityMgrImp::SharedInstance();
  ML_SAFE_ASSERT(instance != NULL, "Null Pointer Error");
  if(instance != NULL) {
    instance->ClearAllEntity();
  }
}
} // namespace magicland