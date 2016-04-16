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

#include "../MLCamera.h"

namespace MagicLand
{
	class MLPlayerCamera;
};

class MagicLand::MLPlayerCamera : public MagicLand::MLCamera
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

#endif // ML_PLAYERCAMERA_MLPLAYERCAMERA_H_