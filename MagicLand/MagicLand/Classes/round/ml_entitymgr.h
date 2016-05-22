//--------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon[1322600812@qq.com]
// Date: 2016 / 05 / 22
// Version: 1.0
// Brief: Manage all the entity in the game
//--------------------------------------------------------------------------
#ifndef ML_ROUND_MLENTITYMGR_H_
#define ML_ROUND_MLENTITYMGR_H_

#include <stdint.h>

namespace magicland {

class MLEntity;

class MLEntityMgr{
public:
  static int32_t Init();
  static void Update(float delta);
  static void Destroy();

  static void AddEntity(MLEntity* entity);
  static void ClearAllEntity();
};

} // namespace magicland
#endif // ML_ROUND_MLENTITYMGR_H