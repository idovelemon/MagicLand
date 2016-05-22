//-----------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon[1322600812@qq.com]
// Date: 2016 / 05 / 22
// Brief: Hold all the speed of the entity
//-----------------------------------------------------
#ifndef ML_ECS_MLCOMSPEED_H_
#define ML_ECS_MLCOMSPEED_H_

#include "ml_component.h"

namespace magicland {

class MLEntity;

class MLComSpeed:public MLComponent{
public:
  MLComSpeed(MLEntity* entity, float pos_speed, float scale_speed, float rot_speed);
  virtual ~MLComSpeed();

public:
  void SetPosSpeed(float pos_speed);
  float GetPosSpeed() const;

  void SetScaleSpeed(float scale_speed);
  float GetScaleSpeed() const;

  void SetRotSpeed(float rot_speed);
  float GetRotSpeed() const;

private:
  float           m_PosSpeed;
  float           m_ScaleSpeed;
  float           m_RotSpeed;
};
} // namespace magicland
#endif // ML_ECS_MLCOMSPEED_H_