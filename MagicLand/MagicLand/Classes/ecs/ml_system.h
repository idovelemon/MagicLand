//-------------------------------------------------------------
// Delcaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon[1322600812@qq.com]
// Date: 2016 / 05 / 22
// Version: 1.0
// Brief: Control the entity's behavior
//-------------------------------------------------------------
#ifndef ML_ECS_MLSYSTEM_H_
#define ML_ECS_MLSYSTEM_H_

#include "marco.h"
#include "ml_entity.h"
#include "reference/ml_reference.h"

namespace magicland{

class MLSystem:public MLReference {
public:
  MLSystem(MLEntity* entity)
  :m_Entity(entity) {
    ML_SAFE_ASSERT(m_Entity != NULL, "Null Pointer Error");
    ML_SAFE_GRAB(m_Entity);
  }

  virtual ~MLSystem() {
    ML_SAFE_DROP(m_Entity);
  }

public:
  virtual void Run(float delta) = 0;

protected:
  MLEntity*   m_Entity;

private:
  ML_DISALLOW_COPY_AND_ASSIGN(MLSystem);
};

} // namespace magicland

#endif // ML_ECS_MLSYSTEM_H_