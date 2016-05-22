//--------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon[1322600812@qq.com]
// Date: 2016 / 05 / 22
// Version: 1.0
// Brief: Config the round
//--------------------------------------------------------------------------
#ifndef ML_ROUND_MLROUNDCONFIG_H_
#define ML_ROUND_MLROUNDCONFIG_H_

#include <stdint.h>

namespace magicland {

class MLRoundConfig {
public:
  static int32_t Init();
  static void Destroy();

  static int32_t ConfigRound(int32_t round);
};

} // namespace magicland

#endif // ML_ROUND_MLROUNDCONFIG_H_