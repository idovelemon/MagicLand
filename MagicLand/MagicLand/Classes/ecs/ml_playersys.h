//-------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon[1322600812@qq.com]
// Date: 2016 / 05 / 22
// Version: 1.0
// Brief: System control player's behavior
//-------------------------------------------------------------------------
#ifndef ML_ECS_MLPLAYERSYS_H_
#define ML_ECS_MLPLAYERSYS_H_

#include "ml_system.h"

namespace magicland {

class MLEntity;

class MLPlayerSys:public MLSystem{
public:
  MLPlayerSys(MLEntity* entity);
  virtual ~MLPlayerSys();

public:
  virtual void Run(float delta);
};

} // namespace magicland

#endif // ML_ECS_MLPLAYERSYS_H_