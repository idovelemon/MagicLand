//------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2015/11/29
// Version: 1.0
// Brief: This file will define the camera that will be used in MagicLand
//------------------------------------------------------------------------
#ifndef ML_CAMERA_MLCAMERA_H_
#define ML_CAMERA_MLCAMERA_H_

#include <cocos2d.h>

#include "../reference/ml_reference.h"

namespace MagicLand
{
	class MLCamera;
};

class MagicLand::MLCamera:public MLReference
{
public:
	MLCamera();
    MLCamera(cocos2d::CCLayer* layer);
    virtual ~MLCamera();

public:
    virtual bool Init() = 0;
    virtual void Update(float delta) = 0;
    virtual void Kill();

public:
    virtual bool IsDead() const;

protected:
    cocos2d::CCLayer*	m_Layer;       // The layer that be controled by the camera
    bool				m_IsDead;      // If the camera is dead
};

#endif // ML_CAMERA_MLCAMERA_H_