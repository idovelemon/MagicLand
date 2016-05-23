//---------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon[1322600812@qq.com]
// Date: 2016 / 05 / 23
// Brief: Evil circle's control system
//---------------------------------------------------------
#ifndef ML_ECS_MLEVILCIRCLESYS_H_
#define ML_ECS_MLEVILCIRCLESYS_H_

#include "ml_system.h"

namespace magicland {

class MLEvilCircleSys:public MLSystem {
public:
  MLEvilCircleSys(MLEntity* entity);
  virtual ~MLEvilCircleSys();

public:
  virtual void Run(float delta);
};

} // namespace magicland

#endif // ML_ECS_MLEVILCIRCLESYS_H_