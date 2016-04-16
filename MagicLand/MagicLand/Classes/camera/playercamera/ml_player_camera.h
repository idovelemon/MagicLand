//------------------------------------------------------------------------
// Declaration: Copyright (c), by LiaoYuhang, 2015. All right reserved.
// Author: LiaoYuhang
// Date: 2016/01/02
// Version: 1.0
// Brief: 
//------------------------------------------------------------------------
#ifndef ML_PLAYERCAMERA_MLPLAYERCAMERA_H_
#define ML_PLAYERCAMERA_MLPLAYERCAMERA_H_

#include <cocos2d.h>

#include "camera/ml_camera.h"

namespace magicland{

class MLPlayerCamera : public MLCamera
{
public:
	MLPlayerCamera();
	MLPlayerCamera(cocos2d::CCLayer* layer);
	virtual ~MLPlayerCamera();

public:
	virtual bool Init();
	virtual void Update(float delta);
	virtual void Kill();

private:
	void calculateCamrea();

public:
	virtual bool IsDead() const;
};

}; // namespace magicland

#endif // ML_PLAYERCAMERA_MLPLAYERCAMERA_H_