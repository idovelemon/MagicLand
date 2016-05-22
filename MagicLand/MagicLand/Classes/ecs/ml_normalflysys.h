//-------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon[1322600812@qq.com]
// Date: 2016 / 05 / 22
// Brief: Control the normal fly and attack
//-------------------------------------------------------------
#ifndef ML_ECS_MLNORMALFLY_H_
#define ML_ECS_MLNORMALFLY_H_

#include "ml_system.h"

namespace magicland {

class MLEntity;

class MLNormalFlySys:public MLSystem {
public:
  MLNormalFlySys(MLEntity* entity);
  virtual ~MLNormalFlySys();

public:
  virtual void Run(float delta);
};

} // namespace magicland

#endif // ML_ECS_MLNORMALFLY_H_