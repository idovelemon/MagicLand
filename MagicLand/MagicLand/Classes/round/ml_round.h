//---------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon[1322600812@qq.com]
// Date: 2016 / 05 / 22
// Version: 1.0
// Brief: Define one round
//---------------------------------------------------------------------
#ifndef ML_ROUND_MLROUNDMGR_H_
#define ML_ROUND_MLROUNDMGR_H_

#include <stdint.h>

namespace magicland {

class MLRoundMgr {
public:
  static const int32_t kMaxRound = 100;

public:
  static int32_t Init();
  static void Update(float delta);
  static void Destroy();

  static void StartRound(int32_t round);
  static void ReStartRound();
  static void PauseRound();
  static void ResumeRound();
  static void StopRound();
};

}
#endif // ML_ROUND_MLROUNDMGR_H_