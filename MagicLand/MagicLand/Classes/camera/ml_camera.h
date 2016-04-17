//------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2015. All right reserved.
// Author: i_dovelemon(1322600812@qq.com)
// Date: 2015/11/29
// Version: 1.0
// Brief: This file will define the camera that will be used in magicland
//------------------------------------------------------------------------
#ifndef ML_CAMERA_MLCAMERA_H_
#define ML_CAMERA_MLCAMERA_H_

#include <cocos2d.h>

#include "marco.h"
#include "reference/ml_reference.h"

namespace magicland {

class MLCamera:public MLReference {
public:
	MLCamera();
  explicit MLCamera(cocos2d::CCLayer* layer);
  virtual ~MLCamera();

public:
  virtual bool Init() = 0;
  virtual void Update(float delta) = 0;
  virtual void Kill();

public:
  virtual bool IsDead() const;

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLCamera);

protected:
  cocos2d::CCLayer*	m_Layer;  // The layer that be controled by the camera
  bool				      m_IsDead; // If the camera is dead
};

}; // namespace magicland

#endif // ML_CAMERA_MLCAMERA_H_