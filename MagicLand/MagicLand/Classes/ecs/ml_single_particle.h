//--------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon[1322600812@qq.com]
// Date: 2016 / 05 / 22
// Brief: Single particle weapon
//--------------------------------------------------
#ifndef ML_ECS_SINGLEPARTICLE_H_
#define ML_ECS_SINGLEPARTICLE_H_

#include "ml_weapon.h"

namespace magicland {

namespace weapon {

class MLSingleParticle:public MLWeapon {
public:
  MLSingleParticle();
  virtual ~MLSingleParticle();

public:
  virtual void Run(float delta);

protected:
  MLEntity* CreateSingleParticle();

private:
  int32_t     m_Delta;
};
} // namespace weapon

} // namespace magicland

#endif // ML_ECS_SINGLEPARTICLE_H_